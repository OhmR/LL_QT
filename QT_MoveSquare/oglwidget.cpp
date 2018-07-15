#include "oglwidget.h"
#include <QGL>
#include <GL/glu.h>
#include <GL/gl.h>
#include <QKeyEvent>

OGLWidget::OGLWidget(QWidget* parent, const char* name, bool fs)//:QGLWidget(parent, name)
{
    xRot = yRot = zRot = 0.0;
    posx = 0, posy = 0, posz = 0;
    Point = new QPoint(320, 240);
    rQuad = 0.0;
    fullScreen = fs;
    setGeometry(0, 0, 640, 480);

    if(fullScreen)
        showFullScreen();
}

OGLWidget::~OGLWidget()
{
}

void OGLWidget::initializeGL(){
    loadGLTextures();
    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_SMOOTH);    //阴影平滑
    glClearColor(1.0, 1.0, 1.0, 0.0);   //R,G,B,Alpha

    glClearDepth(1.0);  //设置深度缓存
    glEnable(GL_DEPTH_TEST);    //启动深度测试
    glDepthFunc(GL_LEQUAL); //所作深度测试类型

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //精细的透视修正，轻微影响性能
}

void OGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕、深度缓存
    glLoadIdentity();   //重置模型观察矩阵

    screen2GLPoint(Point->rx(), Point->ry());

    glTranslatef(posx , posy, posz);

//    rQuad = 56.0;
//    glRotatef(rQuad , 1.0, 1.0, 1.0);   //绕Y轴旋转rQuad度

    glBindTexture(GL_TEXTURE_2D, texture[0]);   //选择纹理

    glBegin(GL_QUADS);      //开始绘制四边形
//        glColor3f(0.7, 0.3, 0.5);   //点的颜色
        glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, 1.0); //以下为四个点的位置
        glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 1.0);
        glTexCoord2f(1.0, 0.0); glVertex2f(1.0, -1.0);
        glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0);
/*
//      glColor3f(1.0, 0.0, 0.0);   //点的颜色
        glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 1.0); //以下为四个点的位置
        glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, -1.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);

//        glColor3f(1.0, 0.5, 0.0);   //点的颜色
        glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, -1.0); //以下为四个点的位置
        glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, -1.0);

//        glColor3f(0.0, 0.5, 1.0);   //点的颜色
        glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0); //以下为四个点的位置
        glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);

//        glColor3f(0.0, 0.0, 1.0);   //点的颜色
        glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0); //以下为四个点的位置
        glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);

//        glColor3f(1.0, 0.0, 0.5);   //点的颜色
        glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, -1.0, -1.0); //以下为四个点的位置
        glTexCoord2f(1.0, 1.0); glVertex3f(1.0, -1.0, -1.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
*/
    glEnd();                //结束绘制四边形
}

void OGLWidget::resizeGL(int width, int height){
    if(height == 0)
        height = 1;

    glViewport(0, 0, (GLint)width, (GLint)height); //重置当前窗口
    glMatrixMode(GL_PROJECTION);    //选择投影矩阵
    glLoadIdentity();               //重置投影矩阵
    gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0); //建立透视投影矩阵
    glMatrixMode(GL_MODELVIEW);     //选择模型观察矩阵
    glLoadIdentity();               //重置模型观察矩阵
}

void OGLWidget::keyPressEvent(QKeyEvent* e){
    switch(e->key()) {
    case Qt::Key_F2:
        fullScreen = !fullScreen;
        if(fullScreen){
            showFullScreen();
        }
        else
        {
            showNormal();
            setGeometry(0,0,640,480);
        }
        updateGL();
        break;
    case Qt::Key_Escape:
        close();
    }
}

void OGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton){
        *Point = e->pos();
        updateGL();
    }
}

void OGLWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        *Point = e->pos();
        printf("%d %d\n",Point->rx(),Point->ry());
        updateGL();
    }
}

void OGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        *Point = e->pos();
        updateGL();
    }
}

void OGLWidget::loadGLTextures()
{
    QImage tex, buf;
    if(!buf.load("F:\\Photo\\2016-10-07-6.bmp"))
    {
        qWarning("Could not read image file, using single-color instead.");
        QImage dummy(128, 128, QImage::Format::Format_ARGB32);
        dummy.fill(Qt::green);
        buf = dummy;
    }
    tex = QGLWidget::convertToGLFormat(buf);

    glGenTextures(1, &texture[0]);  //创建一个纹理
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void OGLWidget::screen2GLPoint(int x, int y){
    GLfloat winx, winy, winz;

//    if()

    winx = x;
    winy = height() - y;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

    glReadPixels((int)winx, (int)winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);
    gluUnProject(winx, winy, winz, mvmatrix, projmatrix, viewport, &posx, &posy, &posz);
//    posz = -6;
//    printf("x = %lf y = %lf z = %lf\n",posx, posy, posz);
    posx /= 15;
    posy /= 15;
    posz /= 15;
}
