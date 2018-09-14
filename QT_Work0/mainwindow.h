#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "canvas.h"

class mainwindow : public QWidget {
 public:
  mainwindow();

 private:
  QGridLayout *glayout;
  QVBoxLayout *vlayout;
  QHBoxLayout *mainlayout;
  canvas *c;
};

#endif  // MAINWINDOW_H
