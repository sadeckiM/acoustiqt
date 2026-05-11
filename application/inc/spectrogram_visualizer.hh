#ifndef SPECTROGRAM_VISUALIZER_H__
#define SPECTROGRAM_VISUALIZER_H__

#include <QImage>
#include <QWidget>
#include <QList>
#include <QRgb>
#include "protocol.hh"

class SpectrogramVisualizer : public QWidget {
  Q_OBJECT
  QRgb magnitudeToColor(double magnitude);
  QImage image;
  static constexpr uint8_t height = Protocol::SAMPLES_PER_PACKET / 2;
  static constexpr uint16_t history_len = 200; 
protected:
  void paintEvent(QPaintEvent *event) override;
public slots:
  void addFFTLine(const QList<double> &lastest_fft);
public:
  explicit SpectrogramVisualizer(QWidget *parent = nullptr);
};

#endif 
