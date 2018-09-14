#include "mainwindow.h"

mainwindow::mainwindow() {
  glayout = new QGridLayout();
  vlayout = new QVBoxLayout();
  mainlayout = new QHBoxLayout();
  c = new canvas(500, 700);

  QPushButton *button1 = new QPushButton("one");
  QPushButton *button2 = new QPushButton("two");

  QObject::connect(button1, &QPushButton::clicked, c,
                   &canvas::GetBlockI2C_RS485);

  glayout->setColumnMinimumWidth(2, 15);
  glayout->setRowStretch(2, 15);

  glayout->addWidget(button1, 0, 0);
  glayout->addWidget(button2, 1, 0);

  vlayout->addWidget(c);

  mainlayout->addLayout(glayout);
  mainlayout->addLayout(vlayout);

  // set the proportion of space allocated for different layouts
  mainlayout->setStretchFactor(glayout, 1);
  mainlayout->setStretchFactor(vlayout, 5);

  this->setLayout(mainlayout);
}
