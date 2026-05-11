#include "fft_processor.hh"
#include <cmath>

FFTProcessor::FFTProcessor(QObject *parent) : QObject(parent) {
  fft_in = static_cast<double*>(fftw_malloc(sizeof(double) * N));
  fft_out = static_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * N));
  fft_plan = fftw_plan_dft_r2c_1d(N, fft_in, fft_out, FFTW_ESTIMATE);
}

void FFTProcessor::calculateMag() {
  QList<double> spectrum;
  spectrum.reserve(N / 2);
  for (int i = 0; i < N / 2; ++i) {
    double real = fft_out[i][0];
    double imag = fft_out[i][1];
    double mag = sqrt(real * real + imag * imag);
    spectrum.append(mag);
  }
  emit spectrumReady(spectrum);
}

void FFTProcessor::handleRawAudio(const QList<int32_t> &raw_samples) {
  if (raw_samples.size() < N) return;

  for (int i = 0; i < N; ++i) {
    double sample = (static_cast<double>(raw_samples[i]) / max_int32_t) * volume_gain;
    double window = 0.5 * (1 - cos(2 * M_PI * i) / N);
    fft_in[i] = sample * window;
  }

  fftw_execute(fft_plan);
  calculateMag();
}

FFTProcessor::~FFTProcessor() {
  fftw_destroy_plan(fft_plan);
  fftw_free(fft_in);
  fftw_free(fft_out);
}
