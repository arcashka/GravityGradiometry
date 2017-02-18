#include "receiver.h"
#include <QtMath>
#include <string>
receiver::receiver()
{
    grav = 0;
    coord = QVector3D(0.0f, 0.0f, 0.0f);
}

receiver::receiver(double x, double y, double z)
{
    grav = 0;
    coord = QVector3D(x, y, z);
}

double receiver::getG(cube &cu)
{
    double gz = 0;
    if(cu.gaussDid)

        for(size_t i = 0; i < 27; i++)
        {
            double dx = coord.x() - cu.gaussPoints[i].x();
            double dy = coord.y() - cu.gaussPoints[i].y();
            double dz = coord.z() - cu.gaussPoints[i].z();

            double r = sqrt(dx * dx + dy * dy + dz * dz);

            gz += cu.jacobian * cu.gaussWeights[i] / (4.0 * M_PI * r * r * r) * dz;
        }
    else
    {
        double dx = coord.x() - cu.getCenter().x();
        double dy = coord.y() - cu.getCenter().y();
        double dz = coord.z() - cu.getCenter().z();
        double r = sqrt(dx * dx + dy * dy + dz * dz);

        gz = cu.getMes() / (4.0 * M_PI * r * r * r) * dz;
    }

    return gz;
}
