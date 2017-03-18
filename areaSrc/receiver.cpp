#include "areaHeaders/receiver.h"
#include <QtMath>
#include <string>
Receiver::Receiver()
{
    grav = 0;
    coord = QVector3D(0.0f, 0.0f, 0.0f);
}

Receiver::Receiver(double x, double y, double z)
{
    grav = 0;
    coord = QVector3D(x, y, z);
}

double Receiver::getG(Cube &cu)
{
    double gz = 0;
    if(cu.getGaussDid())

        for(int i = 0; i < 27; i++)
        {
            double dx = coord.x() - cu.getGaussPoint(i).x();
            double dy = coord.y() - cu.getGaussPoint(i).y();
            double dz = coord.z() - cu.getGaussPoint(i).z();

            double r = sqrt(dx * dx + dy * dy + dz * dz);

            gz += cu.getJacobian() * cu.getGaussWeight(i) / (4.0 * M_PI * r * r * r) * dz;
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
