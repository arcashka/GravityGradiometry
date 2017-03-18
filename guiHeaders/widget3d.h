#ifndef WIDGET3D_H
#define WIDGET3D_H


#include "areaHeaders/area.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtOpenGL>

#if !defined(GL_MULTISAMPLE)
#define GL_MULTISAMPLE  0x809D
#endif

class Widget3d : public QGLWidget
{
    Q_OBJECT

signals:

public slots:

public:
    Area ar;
    explicit Widget3d(QWidget * parent = 0);
    void defaultScene();

private:
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat zTra;
    GLfloat nSca;
    QPoint ptrMousePosition;
                            //реакция на клавиши и мышь
    void scalePlus();
    void scaleMinus();
    void rotateUp();
    void rotateDown();
    void rotateLeft();
    void rotateRight();
    void translateDown();
    void translateUp();

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent* pe);
    void keyPressEvent(QKeyEvent* pe);
};

#endif // WIDGET3D_H
