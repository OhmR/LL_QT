#include <qmessagebox.h>
#include <qapplication.h>
#include "oglwidget.h"

int main(int argc, char **argv)
{
    bool fs = false;
    QApplication a(argc, argv);
    switch (QMessageBox::information(0,
            "Start FullScreen?",
            "Would you like to run in fullscreen mode?",
            QMessageBox::Yes,
            QMessageBox::No | QMessageBox::Default)) {
    case QMessageBox::Yes:
        fs = true;
        break;
    case QMessageBox::No:
        fs = false;
        break;
    }

    OGLWidget w(0,0,fs);
    w.show();

    return a.exec();
}
