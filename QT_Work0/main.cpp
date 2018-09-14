#include <blockparser.h>
#include <mainwindow.h>
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  mainwindow main;
  main.resize(900, 600);
  main.show();

  return a.exec();
}
