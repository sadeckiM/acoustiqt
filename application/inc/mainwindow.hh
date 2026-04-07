#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QDialog>
#include <QStackedWidget>
#include <QLineEdit> 
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

public slots:
    void mainPageWidget();
    void spectrogramPageWidget();
private slots:
    void on_btn_theme_clicked();
    void on_btn_cancel_clicked();
};
#endif // MAINWINDOW_HH
