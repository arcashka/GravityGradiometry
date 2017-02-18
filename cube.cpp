#include "cube.h"
#include <QDebug>


void cube::breakForGauss()
{
    gaussDid = true;

    gaussPoints.resize(27);
    gaussWeights.resize(27);

    static const double gaussPoints1d[3] =
    {
        - sqrt(3.0 / 5.0),
        0.0,
        sqrt(3.0 / 5.0)
    };
    static const double gaussWeights1d[3] =
    {
        5.0 / 9.0,
        8.0 / 9.0,
        5.0 / 9.0
    };

    for(size_t i = 0; i < 3; i++)
        for(size_t j = 0; j < 3; j++)
            for(size_t k = 0; k < 3; k++)
            {
                gaussWeights[(i*3+j)*3+k] = gaussWeights1d[i] * gaussWeights1d[j] * gaussWeights1d[k];
                gaussPoints[(i*3+j)*3+k] = QVector3D(gaussPoints1d[i], gaussPoints1d[j], gaussPoints1d[k]);
            }

    // isit??
    jacobian = mes / 8.0;

    double dx = (nodes[1].x() - nodes[0].x());
    double dy = (nodes[2].y() - nodes[0].y());
    // isit??
    for(size_t j = 0; j < 27; j++)
    {
        gaussPoints[j].setX((gaussPoints[j].x() + 1.0) * dx / 2.0 + nodes[0].x());
        gaussPoints[j].setY((gaussPoints[j].y() + 1.0) * dy / 2.0 + nodes[0].y());
        gaussPoints[j].setZ((gaussPoints[j].z() + 1.0) * (nodes[4].z() - nodes[0].z()) / 2.0 + nodes[0].z());
    }
}

cube::cube(double x, double y, double z, double xmin, double ymin, double zmin, double hx, double hy, double hz) {

    nodes.resize(8);
    nodes[0].setX(x);
    nodes[0].setY(y);
    nodes[0].setZ(z);

    nodes[1].setX(x + hx);
    nodes[1].setY(y);
    nodes[1].setZ(z);

    nodes[2].setX(x);
    nodes[2].setY(y + hy);
    nodes[2].setZ(z);

    nodes[3].setX(x + hx);
    nodes[3].setY(y + hy);
    nodes[3].setZ(z);

    nodes[4].setX(x);
    nodes[4].setY(y);
    nodes[4].setZ(z + hz);

    nodes[5].setX(x + hx);
    nodes[5].setY(y);
    nodes[5].setZ(z + hz);

    nodes[6].setX(x);
    nodes[6].setY(y + hy);
    nodes[6].setZ(z + hz);

    nodes[7].setX(x + hx);
    nodes[7].setY(y + hy);
    nodes[7].setZ(z + hz);


    setMes(hx * hy * hz);

    center = QVector3D(x + hx / 2, y + hy / 2, z + hz / 2);

    coords.setX((x - xmin) / hx);
    coords.setY((y - ymin) / hy);
    coords.setZ((z - zmin) / hz);


    for(size_t i = 0; i < 6; ++i)
        neighbours[i] = -1;
}
