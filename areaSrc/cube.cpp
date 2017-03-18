#include "areaHeaders/cube.h"
#include <QDebug>


void Cube::breakForGauss()
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

Cube::Cube(QVector3D a, AreaProperties& properties, QVector3D ha) {

    nodes.resize(8);
    nodes[0].setX(a.x());
    nodes[0].setY(a.y());
    nodes[0].setZ(a.z());

    nodes[1].setX(a.x() + ha.x());
    nodes[1].setY(a.y());
    nodes[1].setZ(a.z());

    nodes[2].setX(a.x());
    nodes[2].setY(a.y() + ha.y());
    nodes[2].setZ(a.z());

    nodes[3].setX(a.x() + ha.x());
    nodes[3].setY(a.y() + ha.y());
    nodes[3].setZ(a.z());

    nodes[4].setX(a.x());
    nodes[4].setY(a.y());
    nodes[4].setZ(a.z() + ha.z());

    nodes[5].setX(a.x() + ha.x());
    nodes[5].setY(a.y());
    nodes[5].setZ(a.z() + ha.z());

    nodes[6].setX(a.x());
    nodes[6].setY(a.y() + ha.y());
    nodes[6].setZ(a.z() + ha.z());

    nodes[7].setX(a.x() + ha.x());
    nodes[7].setY(a.y() + ha.y());
    nodes[7].setZ(a.z() + ha.z());


    setMes(ha.x() * ha.y() * ha.z());

    center = QVector3D(a.x() + ha.x() / 2,
                       a.y() + ha.y() / 2,
                       a.z() + ha.z() / 2);

    index = Index3D((a.x() - properties.xMin) / ha.x(),
                    (a.y() - properties.yMin) / ha.y(),
                    (a.z() - properties.zMin) / ha.z());


    for(int i = 0; i < 6; ++i)
        neighbours[i] = -1;
}
