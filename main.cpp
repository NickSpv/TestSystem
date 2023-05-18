#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("База тестов по программированию");
  w.show();
  return a.exec();
}
