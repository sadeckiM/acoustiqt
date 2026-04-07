#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->theme_frame->setParent(this);
    ui->theme_frame->hide();
    QObject::connect(ui->btn_spec, SIGNAL(clicked()), this, SLOT(spectrogramPageWidget()));
    QObject::connect(ui->btn_return, SIGNAL(clicked()), this, SLOT(mainPageWidget()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mainPageWidget() {
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void MainWindow::spectrogramPageWidget() {
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_btn_theme_clicked()
{
    ui->theme_frame->show();
    ui->theme_frame->raise();
    int x = (this->width() - ui->theme_frame->width()) / 2;
    int y = (this->height() - ui->theme_frame->height()) / 2;
    ui->theme_frame->move(x, y);
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

