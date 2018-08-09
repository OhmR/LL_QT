#include <QApplication>
#include <QSurfaceFormat>
#include <canvas.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    canvas c(500, 700);
    c.show();

    return a.exec();
}
