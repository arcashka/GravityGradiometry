#ifndef RECEIVER_H
#define RECEIVER_H
#include <QVector3D>
#include "cube.h"

class receiver
{
public:
    receiver();
    receiver(double x, double y, double z);
    double grav;
    QVector3D coord;
    double getG(cube &cu);
};

#endif // RECEIVER_H
