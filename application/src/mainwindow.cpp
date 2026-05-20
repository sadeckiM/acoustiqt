#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "protocol.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
  ui->setupUi(this);
  initObjects();
  setupLayouts();
  initConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mainPageWidget() {
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void MainWindow::initObjects() {
  receiver = new UdpReceiver(Protocol::PORT, this);
  processor = new FFTProcessor(this);
  spectrogram_visualizer = new SpectrogramVisualizer(this);
  spectrum_visualizer = new SpectrumVisualizer(this);
}

void MainWindow::setupLayouts() {
  ui->theme_frame->setParent(this);
  ui->theme_frame->hide();
  ui->horizontalLayout_5->addWidget(spectrogram_visualizer);
}

void MainWindow::initConnections() {
  QObject::connect(ui->btn_spec, &QPushButton::clicked,
                   this, &MainWindow::spectrogramPageWidget);
  QObject::connect(ui->btn_return, &QPushButton::clicked, this, &MainWindow::mainPageWidget);
  QObject::connect(ui->verticalSlider, &QSlider::valueChanged,
                  ui->spinBox, &QSpinBox::setValue);
  QObject::connect(ui->spinBox, &QSpinBox::valueChanged, ui->verticalSlider,
                   &QSlider::setValue);
  QObject::connect(receiver, &UdpReceiver::audioDataReceived, processor,
                   &FFTProcessor::handleRawAudio);
  QObject::connect(processor, &FFTProcessor::spectrumReady, spectrum_visualizer,
                   &SpectrumVisualizer::updateSpectrum);
  QObject::connect(processor, &FFTProcessor::spectrumReady,
                   spectrogram_visualizer,
                   &SpectrogramVisualizer::addFFTLine);
  QObject::connect(ui->verticalSlider, &QSlider::valueChanged,
                     processor, &FFTProcessor::setVolumeGain);
  QObject::connect(processor, &FFTProcessor::spectrumReady, 
                   ui->spectrum_widget, &SpectrumVisualizer::updateSpectrum);
}

void MainWindow::spectrogramPageWidget() {
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_btn_theme_clicked()
{
    int x = (this->width() - ui->theme_frame->width()) / 2;
    int y = (this->height() - ui->theme_frame->height()) / 2;
    ui->theme_frame->move(x, y);

    ui->theme_frame->raise();
    ui->theme_frame->show();
}

void MainWindow::on_btn_cancel_clicked()
{
    ui->theme_frame->hide();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    if(ui->theme_frame && !ui->theme_frame->isHidden()) {
        int x = (this->width() - ui->theme_frame->width()) / 2;
        int y = (this->height() - ui->theme_frame->height()) / 2;
        ui->theme_frame->move(x, y);
        ui->theme_frame->raise();
    }
}

