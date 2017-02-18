#include "widget3d.h"
#include <limits>
#include <QString>
#include <QFont>


Widget3d::Widget3d(QWidget * parent) : QGLWidget(parent)
{
    defaultScene();
}

void Widget3d::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_MULTISAMPLE);
}

void Widget3d::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;
    if(nWidth>=nHeight)
        glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 30.0);
    else
        glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 30.0);

    glViewport(0, 0,(GLint)nWidth, (GLint)nHeight);
}

void Widget3d::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(ar.cubes.size() == 0) return;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double xmin, xmax, ymin, ymax, zmin, zmax;
    xmin = ymin = zmin = std::numeric_limits<double>::max();
    xmax = ymax = zmax = -std::numeric_limits<double>::max();
    for(size_t i = 0; i < ar.cubes.size(); i++)
    {
        for(size_t j = 0; j < 8; j++)
        {
            if(ar.cubes[i].nodes[j].x() > xmax) xmax = ar.cubes[i].nodes[j].x();
            if(ar.cubes[i].nodes[j].y() > ymax) ymax = ar.cubes[i].nodes[j].y();
            if(ar.cubes[i].nodes[j].z() > zmax) zmax = ar.cubes[i].nodes[j].z();
            if(ar.cubes[i].nodes[j].x() < xmin) xmin = ar.cubes[i].nodes[j].x();
            if(ar.cubes[i].nodes[j].y() < ymin) ymin = ar.cubes[i].nodes[j].y();
            if(ar.cubes[i].nodes[j].z() < zmin) zmin = ar.cubes[i].nodes[j].z();
        }
    }

    float xTra = (float)(xmax - xmin) / 2.0f;
    float yTra = (float)(ymax - ymin) / 2.0f;
    zTra = (float)(zmax - zmin) / 2.0f;

    glScalef(nSca, nSca, nSca);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    glTranslatef(-xTra-xmin, zTra+zmin, -yTra-ymin);

    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);


    for(size_t i = 0; i < ar.cubes.size(); i++)
    {
        if(ar.cubes[i].getDensity() > 1e-1)
        {
            double eps = 1.0;
            double color = ar.getColor(ar.cubes[i]);
            glColor3f(color, color, color);

            // отрисовка четырёхугольников
            if(!ar.gaussPointsDraw)
            {
                glBegin(GL_QUADS);
                glVertex3d(ar.cubes[i].nodes[0].x() + eps, ar.cubes[i].nodes[0].y() + eps, ar.cubes[i].nodes[0].z() + eps);
                glVertex3d(ar.cubes[i].nodes[1].x() - eps, ar.cubes[i].nodes[1].y() + eps, ar.cubes[i].nodes[1].z() + eps);
                glVertex3d(ar.cubes[i].nodes[3].x() - eps, ar.cubes[i].nodes[3].y() - eps, ar.cubes[i].nodes[3].z() + eps);
                glVertex3d(ar.cubes[i].nodes[2].x() + eps, ar.cubes[i].nodes[2].y() - eps, ar.cubes[i].nodes[2].z() + eps);

                glVertex3d(ar.cubes[i].nodes[4].x() + eps, ar.cubes[i].nodes[4].y() + eps, ar.cubes[i].nodes[4].z() - eps);
                glVertex3d(ar.cubes[i].nodes[5].x() - eps, ar.cubes[i].nodes[5].y() + eps, ar.cubes[i].nodes[5].z() - eps);
                glVertex3d(ar.cubes[i].nodes[7].x() - eps, ar.cubes[i].nodes[7].y() - eps, ar.cubes[i].nodes[7].z() - eps);
                glVertex3d(ar.cubes[i].nodes[6].x() + eps, ar.cubes[i].nodes[6].y() - eps, ar.cubes[i].nodes[6].z() - eps);

                glVertex3d(ar.cubes[i].nodes[0].x() + eps, ar.cubes[i].nodes[0].y() + eps, ar.cubes[i].nodes[0].z() + eps);
                glVertex3d(ar.cubes[i].nodes[1].x() - eps, ar.cubes[i].nodes[1].y() + eps, ar.cubes[i].nodes[1].z() + eps);
                glVertex3d(ar.cubes[i].nodes[5].x() - eps, ar.cubes[i].nodes[5].y() + eps, ar.cubes[i].nodes[5].z() - eps);
                glVertex3d(ar.cubes[i].nodes[4].x() + eps, ar.cubes[i].nodes[4].y() + eps, ar.cubes[i].nodes[4].z() - eps);

                glVertex3d(ar.cubes[i].nodes[2].x() + eps, ar.cubes[i].nodes[2].y() - eps, ar.cubes[i].nodes[2].z() + eps);
                glVertex3d(ar.cubes[i].nodes[3].x() - eps, ar.cubes[i].nodes[3].y() - eps, ar.cubes[i].nodes[3].z() + eps);
                glVertex3d(ar.cubes[i].nodes[7].x() - eps, ar.cubes[i].nodes[7].y() - eps, ar.cubes[i].nodes[7].z() - eps);
                glVertex3d(ar.cubes[i].nodes[6].x() + eps, ar.cubes[i].nodes[6].y() - eps, ar.cubes[i].nodes[6].z() - eps);

                glVertex3d(ar.cubes[i].nodes[1].x() - eps, ar.cubes[i].nodes[1].y() + eps, ar.cubes[i].nodes[1].z() + eps);
                glVertex3d(ar.cubes[i].nodes[3].x() - eps, ar.cubes[i].nodes[3].y() - eps, ar.cubes[i].nodes[3].z() + eps);
                glVertex3d(ar.cubes[i].nodes[7].x() - eps, ar.cubes[i].nodes[7].y() - eps, ar.cubes[i].nodes[7].z() - eps);
                glVertex3d(ar.cubes[i].nodes[5].x() - eps, ar.cubes[i].nodes[5].y() + eps, ar.cubes[i].nodes[5].z() - eps);

                glVertex3d(ar.cubes[i].nodes[0].x() + eps, ar.cubes[i].nodes[0].y() + eps, ar.cubes[i].nodes[0].z() + eps);
                glVertex3d(ar.cubes[i].nodes[2].x() + eps, ar.cubes[i].nodes[2].y() - eps, ar.cubes[i].nodes[2].z() + eps);
                glVertex3d(ar.cubes[i].nodes[6].x() + eps, ar.cubes[i].nodes[6].y() - eps, ar.cubes[i].nodes[6].z() - eps);
                glVertex3d(ar.cubes[i].nodes[4].x() + eps, ar.cubes[i].nodes[4].y() + eps, ar.cubes[i].nodes[4].z() - eps);
                glEnd();
            }

            // отрисовка точек Гаусса
            else
            {
                if(ar.cubes[i].gaussDid)
                {
                    glColor3f(1.0f, 0.0f, 0.0f);
                    glPointSize(5);
                    glBegin(GL_POINTS);
                    for(int l = 0; l < 27; ++l)
                        glVertex3d(ar.cubes[i].gaussPoints[l].x(), ar.cubes[i].gaussPoints[l].y(), ar.cubes[i].gaussPoints[l].z());
                    glEnd();
                }

            }
        }


        if(ar.drawLines)
        {
            // отисовка всех линий
            glLineWidth(0.5f);
            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_LINE_LOOP);
            glVertex3d(ar.cubes[i].nodes[0].x(), ar.cubes[i].nodes[0].y(), ar.cubes[i].nodes[0].z());
            glVertex3d(ar.cubes[i].nodes[1].x(), ar.cubes[i].nodes[1].y(), ar.cubes[i].nodes[1].z());
            glVertex3d(ar.cubes[i].nodes[3].x(), ar.cubes[i].nodes[3].y(), ar.cubes[i].nodes[3].z());
            glVertex3d(ar.cubes[i].nodes[2].x(), ar.cubes[i].nodes[2].y(), ar.cubes[i].nodes[2].z());
            glEnd();
            glBegin(GL_LINE_LOOP);
            glVertex3d(ar.cubes[i].nodes[4].x(), ar.cubes[i].nodes[4].y(), ar.cubes[i].nodes[4].z());
            glVertex3d(ar.cubes[i].nodes[5].x(), ar.cubes[i].nodes[5].y(), ar.cubes[i].nodes[5].z());
            glVertex3d(ar.cubes[i].nodes[7].x(), ar.cubes[i].nodes[7].y(), ar.cubes[i].nodes[7].z());
            glVertex3d(ar.cubes[i].nodes[6].x(), ar.cubes[i].nodes[6].y(), ar.cubes[i].nodes[6].z());
            glEnd();
            glBegin(GL_LINES);
            glVertex3d(ar.cubes[i].nodes[4].x(), ar.cubes[i].nodes[4].y(), ar.cubes[i].nodes[4].z());
            glVertex3d(ar.cubes[i].nodes[0].x(), ar.cubes[i].nodes[0].y(), ar.cubes[i].nodes[0].z());
            glVertex3d(ar.cubes[i].nodes[5].x(), ar.cubes[i].nodes[5].y(), ar.cubes[i].nodes[5].z());
            glVertex3d(ar.cubes[i].nodes[1].x(), ar.cubes[i].nodes[1].y(), ar.cubes[i].nodes[1].z());
            glVertex3d(ar.cubes[i].nodes[3].x(), ar.cubes[i].nodes[3].y(), ar.cubes[i].nodes[3].z());
            glVertex3d(ar.cubes[i].nodes[7].x(), ar.cubes[i].nodes[7].y(), ar.cubes[i].nodes[7].z());
            glVertex3d(ar.cubes[i].nodes[6].x(), ar.cubes[i].nodes[6].y(), ar.cubes[i].nodes[6].z());
            glVertex3d(ar.cubes[i].nodes[2].x(), ar.cubes[i].nodes[2].y(), ar.cubes[i].nodes[2].z());
            glEnd();
        }
        else
            // отрисовка только линий вокруг кубов
            if(ar.cubes[i].getDensity() > 1e-1)
            {
                glLineWidth(0.5f);
                glColor3f(0.0f, 0.0f, 0.0f);
                glBegin(GL_LINE_LOOP);
                glVertex3d(ar.cubes[i].nodes[0].x(), ar.cubes[i].nodes[0].y(), ar.cubes[i].nodes[0].z());
                glVertex3d(ar.cubes[i].nodes[1].x(), ar.cubes[i].nodes[1].y(), ar.cubes[i].nodes[1].z());
                glVertex3d(ar.cubes[i].nodes[3].x(), ar.cubes[i].nodes[3].y(), ar.cubes[i].nodes[3].z());
                glVertex3d(ar.cubes[i].nodes[2].x(), ar.cubes[i].nodes[2].y(), ar.cubes[i].nodes[2].z());
                glEnd();
                glBegin(GL_LINE_LOOP);
                glVertex3d(ar.cubes[i].nodes[4].x(), ar.cubes[i].nodes[4].y(), ar.cubes[i].nodes[4].z());
                glVertex3d(ar.cubes[i].nodes[5].x(), ar.cubes[i].nodes[5].y(), ar.cubes[i].nodes[5].z());
                glVertex3d(ar.cubes[i].nodes[7].x(), ar.cubes[i].nodes[7].y(), ar.cubes[i].nodes[7].z());
                glVertex3d(ar.cubes[i].nodes[6].x(), ar.cubes[i].nodes[6].y(), ar.cubes[i].nodes[6].z());
                glEnd();
                glBegin(GL_LINES);
                glVertex3d(ar.cubes[i].nodes[4].x(), ar.cubes[i].nodes[4].y(), ar.cubes[i].nodes[4].z());
                glVertex3d(ar.cubes[i].nodes[0].x(), ar.cubes[i].nodes[0].y(), ar.cubes[i].nodes[0].z());
                glVertex3d(ar.cubes[i].nodes[5].x(), ar.cubes[i].nodes[5].y(), ar.cubes[i].nodes[5].z());
                glVertex3d(ar.cubes[i].nodes[1].x(), ar.cubes[i].nodes[1].y(), ar.cubes[i].nodes[1].z());
                glVertex3d(ar.cubes[i].nodes[3].x(), ar.cubes[i].nodes[3].y(), ar.cubes[i].nodes[3].z());
                glVertex3d(ar.cubes[i].nodes[7].x(), ar.cubes[i].nodes[7].y(), ar.cubes[i].nodes[7].z());
                glVertex3d(ar.cubes[i].nodes[6].x(), ar.cubes[i].nodes[6].y(), ar.cubes[i].nodes[6].z());
                glVertex3d(ar.cubes[i].nodes[2].x(), ar.cubes[i].nodes[2].y(), ar.cubes[i].nodes[2].z());
                glEnd();
            }
    }
      glColor3f(1.0f, 0.0f, 0.0f);
      glLineWidth(5.0f);
      glBegin(GL_LINES);
      glVertex3d(xmin, ymin, zmin);
      glVertex3d(xmax, ymin, zmin);
      glEnd();

      glColor3f(0.0f, 0.0f, 0.0f);
      glDisable(GL_DEPTH_TEST);
      renderText(xmax, ymin, zmin, QString("x"), QFont("Times", 20, QFont::Bold));
      glEnable(GL_DEPTH_TEST);

      glColor3f(0.0f, 1.0f, 0.0f);
      glBegin(GL_LINES);
      glVertex3d(xmin, ymin, zmin);
      glVertex3d(xmin, ymax, zmin);
      glEnd();

      glColor3f(0.0f, 0.0f, 0.0f);
      glDisable(GL_DEPTH_TEST);
      renderText(xmin, ymax, zmin, QString("y"), QFont("Times", 20, QFont::Bold));
      glEnable(GL_DEPTH_TEST);

      glColor3f(0.0f, 0.0f, 1.0f);
      glBegin(GL_LINES);
      glVertex3d(xmin, ymin, zmin);
      glVertex3d(xmin, ymin, zmax);
      glEnd();

      glColor3f(0.0f, 0.0f, 0.0f);
      glDisable(GL_DEPTH_TEST);
      renderText(xmin, ymin, zmax, QString("z"), QFont("Times", 20, QFont::Bold));
      glEnable(GL_DEPTH_TEST);
}

void Widget3d::mousePressEvent(QMouseEvent * pe)
{
    ptrMousePosition = pe->pos();
}

void Widget3d::mouseReleaseEvent(QMouseEvent *)
{
    updateGL();
}

void Widget3d::mouseMoveEvent(QMouseEvent * pe)
{
    xRot += 180 / 1.5 * (GLfloat)(pe->y() - ptrMousePosition.y())/height();
    yRot += 180 / 1.5 * (GLfloat)(pe->x() - ptrMousePosition.x())/width();
    ptrMousePosition = pe->pos();
    updateGL();
}

void Widget3d::wheelEvent(QWheelEvent * pe)
{
    if((pe->delta())>0) scalePlus();
    else if((pe->delta())<0) scaleMinus();

    updateGL();
}

void Widget3d::keyPressEvent(QKeyEvent * pe)
{
    switch(pe->key())
    {
    case Qt::Key_Plus:
        scalePlus();
        break;

    case Qt::Key_Equal:
        scalePlus();
        break;

    case Qt::Key_Minus:
        scaleMinus();
        break;

    case Qt::Key_Up:
        rotateUp();
        break;

    case Qt::Key_Down:
        rotateDown();
        break;

    case Qt::Key_Left:
        rotateLeft();
        break;

    case Qt::Key_Right:
        rotateRight();
        break;

    case Qt::Key_Z:
        translateDown();
        break;

    case Qt::Key_X:
        translateUp();
        break;

    case Qt::Key_Space:
        defaultScene();
        break;

    case Qt::Key_Escape:
        this->close();
        break;
    }

    updateGL();
}

void Widget3d::scalePlus()
{
    nSca = nSca * 1.1f;
}

void Widget3d::scaleMinus()
{
    nSca = nSca / 1.1f;
}

void Widget3d::rotateUp()
{
    xRot += 1.0f;
}

void Widget3d::rotateDown()
{
    xRot -= 1.0f;
}

void Widget3d::rotateLeft()
{
    zRot += 1.0f;
}

void Widget3d::rotateRight()
{
    zRot -= 1.0f;
}

void Widget3d::translateDown()
{
    zTra -= 10.0f;//0.05f;
}

void Widget3d::translateUp()
{
    zTra += 10.0f;//0.05f;
}

void Widget3d::defaultScene()
{
    xRot = 0.0f;
    yRot = 0.0f;
    zRot = 0.0f;
    zTra = 0.0f;
    nSca = 0.001f;
}
