#ifndef FFT_PROCESSOR_H__
#define FFT_PROCESSOR_H__

#include <QObject> 
#include <fftw3.h>
#include "protocol.hh"
#include <limits>
#include <QList>

class FFTProcessor : public QObject {
  Q_OBJECT 
  void applyWindow();
  double max_int32_t = std::numeric_limits<int32_t>::max();
  double volume_gain = 1.0;
  fftw_plan fft_plan;
  double *fft_in;
  fftw_complex *fft_out;
  static constexpr uint16_t N = Protocol::SAMPLES_PER_PACKET;
  void calculateMag();
public:
  explicit FFTProcessor(QObject *parent = nullptr);
  ~FFTProcessor();
public slots:
  void handleRawAudio(const QList<int32_t> &samples);
signals:
  void spectrumReady(const QList<double> &magnitudes);
};

#endif 
