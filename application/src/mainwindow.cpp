/**
 * @file mainwindow.cpp
 * @author Michał Sadecki (michal.sadecki@proton.me)
 * @brief 
 * @version 0.1
 * @date 2026-04-22
 *
 * @copyright Copyright (c) 2026 Michał Sadecki
 */

#include "mainwindow.hh"
#include "ui_mainwindow.h"

/**
 * @brief Konstruktor inicjalizujący główne okno aplikacji. Ustawia sygnały i sloty.
 *
 * @param[in] parent wskaźnik na rodzica MainWindow.
 */
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

/**
 * @brief Domyślny destruktor głównego okna aplkacji.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Obsługuje główny widżet wizualizacji widma.
 */
void MainWindow::mainPageWidget() {
    ui->stackedWidget->setCurrentWidget(ui->page);
}

/**
 * @brief Obsługuje widżet spektrogramu.
 */
void MainWindow::spectrogramPageWidget() {
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

/**
 * @brief Obsługuje wciśnięcie przycisku "Theme".
 */
void MainWindow::on_btn_theme_clicked()
{
    ui->theme_frame->show();
    ui->theme_frame->raise();
    int x = (this->width() - ui->theme_frame->width()) / 2;
    int y = (this->height() - ui->theme_frame->height()) / 2;
    ui->theme_frame->move(x, y);
}


/**
 * @brief Obsługuje wciśnięcie przycisku "Cancel".
 */
void MainWindow::on_btn_cancel_clicked()
{
    ui->theme_frame->hide();
}

/**
 * @brief Przelicza rozmiar okna w zależności od skali ustalonej przez
 * użytkownika.
 *
 * @param event Wskaźnik na zdarzenie.
 */
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    if(ui->theme_frame && !ui->theme_frame->isHidden()) {
        int x = (this->width() - ui->theme_frame->width()) / 2;
        int y = (this->height() - ui->theme_frame->height()) / 2;
        ui->theme_frame->move(x, y);
        ui->theme_frame->raise();
    }
}

