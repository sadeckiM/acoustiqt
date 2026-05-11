#ifndef SPECTRUM_VISUALIZER_H__
#define SPECTRUM_VISUALIZER_H__

#include <QObject>
#include <QList>
#include <QWidget>

class SpectrumVisualizer : public QWidget {
  Q_OBJECT 
public:
  explicit SpectrumVisualizer(QWidget *parent = nullptr);
public slots:
  void updateSpectrum(const QList<double> &data);
protected:
  void paintEvent(QPaintEvent *event) override;
};

#endif 
