#include "guiHeaders/Widget3dSecond.h"
#include <limits>


Widget3dSecond::Widget3dSecond(QWidget * parent) : QGLWidget(parent)
{
    defaultScene();
}

void Widget3dSecond::initializeGL()
{
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_MULTISAMPLE);
}

void Widget3dSecond::resizeGL(int nWidth, int nHeight)
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


void Widget3dSecond::paintGlProj()
{

    if(side == 1)
    {
        xRot = 0.0f;
        yRot = 90.0f;
        zRot = 0.0f;
    }
    if(side == 2)
    {
        xRot = 0.0f;
        yRot = 0.0f;
        zRot = 0.0f;
    }
    if(side == 3)
    {
        xRot = 90.0f;
        yRot = 0.0f;
        zRot = 0.0f;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(ar.getCubes().size() == 0) return;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glScalef(nSca, nSca, nSca);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    glTranslatef(-xTra-xmin, zTra+zmin, -yTra-ymin);

    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    double eps = 1.0;


    for(size_t i = 0; i < ar.getCubes().size(); i++)
    {

        if(check(ar.getCubes()[i]))
        {
            // цвет
            double color = 0.5f;//ar.getColor(ar.cubes[i]);
            glColor3f(color, color, color);


            // кубы
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

            // линии
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


            // текст
            glDisable(GL_DEPTH_TEST);
            glColor3f(0.0f, 0.0f, 1.0f);
            float scaleFont = nSca / 0.00001f;
            switch(side)
            {
            case 1:
                renderText(ar.cubes[i].getCenter().x(), ar.cubes[i].getCenter().y() / 4 + 3 * ar.cubes[i].nodes[0].y() / 4, ar.cubes[i].getCenter().z(),
                           QString::number(ar.cubes[i].getDensity()),QFont("Times", 10 - scaleFont, QFont::Bold));
                break;
            case 2:
                renderText(ar.cubes[i].getCenter().x() / 4 + 3 * ar.cubes[i].nodes[0].x() / 4, ar.cubes[i].getCenter().y(), ar.cubes[i].getCenter().z(),
                           QString::number(ar.cubes[i].getDensity()),QFont("Times", 10 - scaleFont, QFont::Bold));
                break;
            case 3:
                renderText(ar.cubes[i].getCenter().x() / 4 + 3 * ar.cubes[i].nodes[0].x() / 4, ar.cubes[i].getCenter().y(), ar.cubes[i].getCenter().z(),
                           QString::number(ar.cubes[i].getDensity()),QFont("Times", 10 - scaleFont, QFont::Bold));
                break;
            }
            glEnable(GL_DEPTH_TEST);
        }
    }

    double mul = strtnSca / nSca;

    if(side != 1)
    {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex3d(xmin, ymin, zmin);
        glVertex3d(xmax, ymin, zmin);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glDisable(GL_DEPTH_TEST);
        renderText(xmax, ymin, zmin, QString("x"), QFont("Times", 20, QFont::Bold));
        glEnable(GL_DEPTH_TEST);
    }

    if(side != 2)
    {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex3d(xmin, ymin, zmin);
        glVertex3d(xmin, ymax, zmin);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glDisable(GL_DEPTH_TEST);
        renderText(xmin, ymax, zmin, QString("y"), QFont("Times", 20, QFont::Bold));
        glEnable(GL_DEPTH_TEST);
    }

    if(side != 3)
    {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        glVertex3d(xmin, ymin, zmin);
        glVertex3d(xmin, ymin, zmax);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        glDisable(GL_DEPTH_TEST);
        renderText(xmin, ymin, zmax, QString("z"), QFont("Times", 20, QFont::Bold));
        glEnable(GL_DEPTH_TEST);
    }




    double tempAvg = ((ar.xMax - ar.xMin) + (ar.yMax - ar.yMin) + (ar.zMax - ar.zMin)) / 3;
    tempAvg /= 100;
    // по иксу
    if(side == 1)
    {
        // для Y
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        for(size_t linesX = 1; linesX <= (ar.yMax - ar.yMin) / 100; ++linesX)
        {
            glVertex3d(xmin, ymin + linesX * 100, zmin - 20 * mul);
            glVertex3d(xmin, ymin + linesX * 100, zmin + 20 * mul);
        }
        glEnd();

        for(size_t linesX = 1; linesX <= (ar.yMax - ar.yMin) / 100; ++linesX)
        {
            glColor3f(0.0f, 0.0f, 0.0f);
            glDisable(GL_DEPTH_TEST);
            if(1 / mul < 1)
                renderText(xmin, ymin + linesX * 100, zmin - 100 * mul, QString::number(linesX * 100), QFont("Times", 10 * 1 / mul, QFont::Bold));
            else
                renderText(xmin, ymin + linesX * 100, zmin - 100 * mul, QString::number(linesX * 100), QFont("Times", 10, QFont::Bold));
            glEnable(GL_DEPTH_TEST);
        }

        // для Z
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        for(size_t linesX = 1; linesX <= (ar.zMax - ar.zMin) / 100; ++linesX)
        {
            glVertex3d(xmin, ymin - 20 * mul, zmin + linesX * 100);
            glVertex3d(xmin, ymin + 20 * mul,zmin + linesX * 100);
        }
        glEnd();

        for(size_t linesX = 1; linesX <= (ar.zMax - ar.zMin) / 100; ++linesX)
        {
            glColor3f(0.0f, 0.0f, 0.0f);
            glDisable(GL_DEPTH_TEST);
            if (1 / mul < 1)
                renderText(xmin, ymin - 100 * mul, zmin + linesX * 100, QString::number(linesX * 100), QFont("Times", 10 * 1 / mul, QFont::Bold));
            else
                renderText(xmin, ymin - 100 * mul, zmin + linesX * 100, QString::number(linesX * 100), QFont("Times", 10, QFont::Bold));
            glEnable(GL_DEPTH_TEST);
        }
    }

    // по Y
    if(side == 2)
    {   // для X
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        for(size_t linesY = 1; linesY <= (ar.xMax - ar.xMin) / 100; ++linesY)
        {
            glVertex3d(xmin + linesY * 100, ymin, zmin - 20 * mul);
            glVertex3d(xmin  + linesY * 100, ymin, zmin + 20 * mul);
        }
        glEnd();

        for(size_t linesX = 1; linesX <= (ar.xMax - ar.xMin) / 100; ++linesX)
        {
            glColor3f(0.0f, 0.0f, 0.0f);
            glDisable(GL_DEPTH_TEST);
            if(1 / mul < 1)
                renderText(xmin  + linesX * 100, ymin, zmin - 100 * mul, QString::number(linesX * 100), QFont("Times", 10 * 1 / mul, QFont::Bold));
            else
                renderText(xmin  + linesX * 100, ymin, zmin - 100 * mul, QString::number(linesX * 100), QFont("Times", 10, QFont::Bold));
            glEnable(GL_DEPTH_TEST);
        }

        // для Z
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        for(size_t linesX = 1; linesX <= (ar.zMax - ar.zMin) / 100; ++linesX)
        {
            glVertex3d(xmin - 20 * mul, ymin, zmin + linesX * 100);
            glVertex3d(xmin + 20 * mul, ymin ,zmin + linesX * 100);
        }
        glEnd();

        for(size_t linesX = 1; linesX <= (ar.zMax - ar.zMin) / 100; ++linesX)
        {
            glColor3f(0.0f, 0.0f, 0.0f);
            glDisable(GL_DEPTH_TEST);
            if(1 / mul < 1)
                renderText(xmin - 100 * mul, ymin, zmin + linesX * 100, QString::number(linesX * 100), QFont("Times", 10 * 1 / mul, QFont::Bold));
            else
                renderText(xmin - 100 * mul, ymin, zmin + linesX * 100, QString::number(linesX * 100), QFont("Times", 10, QFont::Bold));
            glEnable(GL_DEPTH_TEST);
        }
    }

    // по Z
    if(side == 3)
    {
        // для X
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        for(size_t linesX = 1; linesX <= (ar.xMax - ar.xMin) / 100; ++linesX)
        {
            glVertex3d(xmin  + linesX * 100, ymin + 20 * mul, zmin);
            glVertex3d(xmin  + linesX * 100, ymin - 20 * mul, zmin);
        }
        glEnd();

        for(size_t linesX = 1; linesX <= (ar.xMax - ar.xMin) / 100; ++linesX)
        {
            glColor3f(0.0f, 0.0f, 0.0f);
            glDisable(GL_DEPTH_TEST);
            if(1 / mul < 1)
                renderText(xmin + linesX * 100, ymin - 100 * mul, zmin, QString::number(linesX * 100), QFont("Times", 10 * 1 / mul, QFont::Bold));
            else
                renderText(xmin + linesX * 100, ymin - 100 * mul, zmin, QString::number(linesX * 100), QFont("Times", 10, QFont::Bold));
            glEnable(GL_DEPTH_TEST);
        }

        // для Y
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINES);
        for(size_t linesX = 1; linesX <= (ar.yMax - ar.yMin) / 100; ++linesX)
        {
            glVertex3d(xmin - 20 * mul, ymin + linesX * 100, zmin);
            glVertex3d(xmin + 20 * mul, ymin + linesX * 100, zmin);
        }
        glEnd();

        for(size_t linesX = 1; linesX <= (ar.yMax - ar.yMin) / 100; ++linesX)
        {
            glColor3f(0.0f, 0.0f, 0.0f);
            glDisable(GL_DEPTH_TEST);
            if(1 / mul < 1)
                renderText(xmin - 100 * mul, ymin + linesX * 100, zmin, QString::number(linesX * 100), QFont("Times", 10 * 1 / mul, QFont::Bold));
            else
                renderText(xmin - 100 * mul, ymin + linesX * 100, zmin, QString::number(linesX * 100), QFont("Times", 10, QFont::Bold));
            glEnable(GL_DEPTH_TEST);
        }


    }
}


bool Widget3dSecond::check(Cube cu)
{
    switch(side)
    {
    case 1:
        if(cu.coords.x() == plane)
            return true;
        return false;
    case 2:
        if(cu.coords.y() == plane)
            return true;
        return false;
    case 3:
        if(cu.coords.z() == plane)
            return true;
        return false;
    }
}


void Widget3dSecond::paintGL()
{
    if(side != -1)
        paintGlProj();
    else
        paintGlwoutProj();
}


void Widget3dSecond::paintGlwoutProj()
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
        if(ar.cubes[i].getDensity() > 1e-6)
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
                glColor3f(1.0f, 0.0f, 0.0f);
                glPointSize(5);
                glBegin(GL_POINTS);
                for(int l = 0; l < 27; ++l)
                    glVertex3d(ar.cubes[i].gaussPoints[l].x(), ar.cubes[i].gaussPoints[l].y(), ar.cubes[i].gaussPoints[l].z());
                glEnd();
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
            if(ar.cubes[i].getDensity() > 1e-6)
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


void Widget3dSecond::mousePressEvent(QMouseEvent * pe)
{
    ptrMousePosition = pe->pos();
}

void Widget3dSecond::mouseReleaseEvent(QMouseEvent *)
{
    updateGL();
}

void Widget3dSecond::mouseMoveEvent(QMouseEvent * pe)
{
    switch(side)
    {
    case -1:
        xRot += 180 / 1.5 * (GLfloat)(pe->y() - ptrMousePosition.y())/height();
        yRot += 180 / 1.5 * (GLfloat)(pe->x() - ptrMousePosition.x())/width();
        ptrMousePosition = pe->pos();
        updateGL();
        break;
    case 1:
        zTra += 2 * (GLfloat)(pe->y() - ptrMousePosition.y()) / (nSca * 0.63f / (strtnSca));
        yTra -= 2 * (GLfloat)(pe->x() - ptrMousePosition.x()) / (nSca * 0.63f / (strtnSca));
        ptrMousePosition = pe->pos();
        updateGL();
        break;
    case 2:
        zTra += 2 * (GLfloat)(pe->y() - ptrMousePosition.y()) / (nSca * 0.63f / (strtnSca));
        xTra -= 2 * (GLfloat)(pe->x() - ptrMousePosition.x()) / (nSca * 0.63f / (strtnSca));
        ptrMousePosition = pe->pos();
        updateGL();
        break;
    case 3:
        yTra += 2 * (GLfloat)(pe->y() - ptrMousePosition.y()) / (nSca * 0.63f / (strtnSca));
        xTra -= 2 * (GLfloat)(pe->x() - ptrMousePosition.x()) / (nSca * 0.63f / (strtnSca));
        ptrMousePosition = pe->pos();
        updateGL();
        break;
    default:
        break;
    }
}

void Widget3dSecond::wheelEvent(QWheelEvent * pe)
{
    if((pe->delta())>0) scalePlus();
    else if((pe->delta())<0) scaleMinus();

    updateGL();
}

void Widget3dSecond::keyPressEvent(QKeyEvent * pe)
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

void Widget3dSecond::scalePlus()
{
    nSca = nSca * 1.1f;
}

void Widget3dSecond::scaleMinus()
{
    nSca = nSca / 1.1f;
}

void Widget3dSecond::rotateUp()
{
    if(side == -1)
        xRot += 1.0f;
    else
        xTra -= 1.0f;
}

void Widget3dSecond::rotateDown()
{
    if(side == -1)
        xRot -= 1.0f;
    else
        xTra += 50.0f;
}

void Widget3dSecond::rotateLeft()
{
    if(side == -1)
        zRot += 1.0f;
    else
        zTra -= 0.2f;

}

void Widget3dSecond::rotateRight()
{
    if(side == -1)
        zRot -= 1.0f;
    else
        zTra += 1.0f;
}

void Widget3dSecond::translateDown()
{
    zTra -= 10.0f;//0.05f;
}

void Widget3dSecond::translateUp()
{
    zTra += 10.0f;//0.05f;
}

void Widget3dSecond::defaultScene()
{
    xRot = 0.0f;
    yRot = 0.0f;
    zRot = 0.0f;
    nSca = 0.001f;
    strtnSca = 0.001f;
}

void Widget3dSecond::recalc()
{
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

    xTra = (float)(xmax - xmin) / 2.0f;
    yTra = (float)(ymax - ymin) / 2.0f;
    zTra = (float)(zmax - zmin) / 2.0f;
}
