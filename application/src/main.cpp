#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[]) {
  qSetMessagePattern("[%{type}] %{function}: %{message}");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return QCoreApplication::exec();
}
