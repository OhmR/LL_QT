#include <QApplication>
#include <QSurfaceFormat>
#include <canvas.h>
#include <blockparser.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BlockParser p("/home/cn/test.json");
    qDebug()<<p.getBlockName();
    canvas c(500, 700);
    c.show();

    return a.exec();
}
