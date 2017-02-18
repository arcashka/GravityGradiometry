#ifndef WIDGET3DSECOND_H
#define WIDGET3DSECOND_H


#include "area.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtOpenGL>

#if !defined(GL_MULTISAMPLE)
#define GL_MULTISAMPLE  0x809D
#endif

class Widget3dSecond : public QGLWidget
{
    Q_OBJECT

signals:

public slots:

public:
    area ar;
    explicit Widget3dSecond(QWidget * parent = 0);
    void defaultScene();
    int side = -1;
    int plane = 0;
    void recalc();
private:
    double xmin, xmax, ymin, ymax, zmin, zmax;
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat zTra;
    GLfloat xTra;
    GLfloat yTra;
    GLfloat nSca;
    GLfloat strtnSca;
    QPoint ptrMousePosition;

    bool check(cube cu);
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
    void paintGlProj();
    void paintGlwoutProj();
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent* pe);
    void keyPressEvent(QKeyEvent* pe);
};

#endif // WIDGET3DSECOND_H
