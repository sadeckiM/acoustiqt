#include "fft_processor.hh"
#include <cmath>
#include "audio_config.hh"
#include <QDebug>

FFTProcessor::FFTProcessor(QObject *parent) : QObject(parent) {
  fft_in = static_cast<double*>(fftw_malloc(sizeof(double) * AudioConfig::N));
  fft_out = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * AudioConfig::N));
  fft_plan = fftw_plan_dft_r2c_1d(AudioConfig::N, fft_in, fft_out, FFTW_ESTIMATE);
}

QList<double> FFTProcessor::calculateMag() {
  QList<double> spectrum;
  spectrum.reserve(AudioConfig::N / 2);
  for (uint16_t i = 0; i < AudioConfig::N / 2; ++i) {
    double real = fft_out[i][0];
    double imag = fft_out[i][1];
    double mag = sqrt(real * real + imag * imag);
    spectrum.append(mag);
  }
  // qDebug() << "Magnitude: " << spectrum[0];
  return spectrum;
}

void FFTProcessor::handleRawAudio(const QList<int32_t> &raw_samples) {
  if (raw_samples.size() < AudioConfig::N) return;

  // qDebug() << "FFT dostało " << raw_samples.size() << "próbek, gain: " <<
  //   volume_gain;
  // qDebug() << "Próbka:" << raw_samples[0];

  for (uint16_t i = 0; i < AudioConfig::N; ++i) {
    double sample = (static_cast<double>(raw_samples[i]) /
      AudioConfig::MAX_INT32_T) * volume_gain;
    double window = 0.5 * (1 - cos(2 * M_PI * i) / AudioConfig::N);
    fft_in[i] = sample * window;
  }

  fftw_execute(fft_plan);
  AudioStats stats;
  QList<double> magnitudes = calculateMag();
  stats.dominant_freq = calculateDominantFreq(magnitudes);
  stats.rms = calculateRMS(raw_samples);
  stats.zcr = calculateZCR(raw_samples);
  emit spectrumReady(magnitudes);
  emit statsReady(stats);
}

double FFTProcessor::calculateRMS(const QList<int32_t> &raw_samples) {
  if (raw_samples.isEmpty()) return 0.0;

  double sum = 0;
  for (uint16_t i = 0; i < AudioConfig::N; ++i) {
    double normalized_sample = static_cast<double>(raw_samples[i] / AudioConfig::MAX_INT32_T);
    sum += normalized_sample * normalized_sample;
  }
  return std::sqrt(sum / AudioConfig::N);
}

double FFTProcessor::getDecibels(const QList<int32_t> &raw_samples) { 
  double rms = calculateRMS(raw_samples);
  if (rms < 0.00001) return 0.0;
  return 20 * std::log10(rms) + AudioConfig::NOISE_THRESHOLD;
}

double FFTProcessor::calculateDominantFreq(const QList<double> &magnitudes) {
  if (magnitudes.isEmpty()) return 0.0;
  QList<double>::const_iterator it = std::max_element(magnitudes.begin(), magnitudes.end());
  uint16_t max_index = std::distance(magnitudes.begin(), it);
  return max_index * (AudioConfig::SAMPLE_RATE / static_cast<double>(AudioConfig::N));
}

uint16_t FFTProcessor::calculateZCR(const QList<int32_t> &raw_samples) {
  if (raw_samples.isEmpty()) return 0.0;

  uint16_t crossings = 0;
  for (uint16_t i = 0; i < AudioConfig::N; ++i) {
    if (raw_samples[i - 1] > 0 && raw_samples[i] < 0)
      ++crossings;
    else if (raw_samples[i - 1] < 0 && raw_samples[i] > 0)
        ++crossings;
  }
  return crossings;
}

double FFTProcessor::calculatePeak(const QList<int32_t> &raw_samples) {
  if (raw_samples.isEmpty()) return 0.0;

  QList<int32_t>::const_iterator it = std::max_element(raw_samples.begin(),
                                                       raw_samples.end(),
                                                       [](int32_t a, int32_t b) {
    return std::abs(a) < std::abs(b);
  }); 
  return std::abs(*it) / AudioConfig::MAX_INT32_T; 
}

FFTProcessor::~FFTProcessor() {
  fftw_destroy_plan(fft_plan);
  fftw_free(fft_in);
  fftw_free(fft_out);
}
