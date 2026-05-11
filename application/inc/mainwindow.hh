#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QDialog>
#include <QStackedWidget>
#include <QLineEdit> 
#include <QPushButton>
#include <QLabel>
#include <QResizeEvent>
#include "udp_receiver.hh"
#include "spectrum_visualizer.hh"
#include "fft_processor.hh"

QT_BEGIN_NAMESPACE
namespace Ui {
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Ui::MainWindow *ui;
  UdpReceiver *receiver;
  FFTProcessor *processor;
  SpectrumVisualizer *visualizer;
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;
protected:
  void resizeEvent(QResizeEvent *event) override;
public slots:
  void mainPageWidget();
  void spectrogramPageWidget();
private slots:
  void on_btn_theme_clicked();
  void on_btn_cancel_clicked();
};
#endif // MAINWINDOW_HH
