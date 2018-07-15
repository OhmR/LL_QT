#ifndef OGLTEST_H
#define OGLTEST_H

#include <QtOpenGL/qgl.h>
#include <QWidget>

class OGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    OGLWidget(QWidget* parent = 0, const char* name = 0, bool fs = false);
    ~OGLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void loadGLTextures();  //处理纹理图案
    void screen2GLPoint(int x, int y);
    bool fullScreen;        //保存窗口是否处于全屏状态
    QPoint *Point;
//    QPoint endPoint;
    GLfloat rQuad;
    GLfloat xRot, yRot, zRot;
    GLdouble posx, posy, posz;
    GLfloat zoom;
    GLfloat xSpeed, ySpeed;
    GLuint texture[3];      //存储一个纹理
    GLint viewport[4];
    GLdouble mvmatrix[16], projmatrix[16];
};

#endif // OGLTEST_H
