#include "spectrogram_visualizer.hh"
#include <QPainter>
#include <QRect>
#include <QtMinMax>
#include "audio_config.hh"

SpectrogramVisualizer::SpectrogramVisualizer(QWidget *parent) : QWidget(parent)
  {}

void SpectrogramVisualizer::addFFTLine(const QList<double> &latest_fft) {
  uint16_t w = image.width();
  uint16_t h = image.height();
  QRect sourceRect(1, 0, w - 1, h);
  QImage copy = image.copy(sourceRect);

  QPainter painter(&image);
  painter.drawImage(0, 0, copy);

  for (int y = 0; y < latest_fft.size(); ++y) {
    image.setPixel(w - 1, h - 1 - y,
                   magnitudeToColor(latest_fft[y]));
  }
  update();
}

QRgb SpectrogramVisualizer::magnitudeToColor(double magnitude) {
  double db = 20 * std::log10(magnitude + AudioConfig::epsilon) + AudioConfig::noise_treshold;
  int val = qBound(0, static_cast<int32_t>((db / AudioConfig::noise_treshold) * AudioConfig::max_uint8_t),
                   static_cast<int32_t>(AudioConfig::max_uint8_t));
  return qRgb(val, val / 2, val / 4);
}

void SpectrogramVisualizer::paintEvent(QPaintEvent *event) {

}
