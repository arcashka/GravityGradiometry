#ifndef RECEIVER_H
#define RECEIVER_H
#include <QVector3D>
#include "areaHeaders/cube.h"

class Receiver
{
public:
    Receiver();
    Receiver(double x, double y, double z);
    double grav;
    QVector3D coord;
    // внимание
    // возвращает вклад в z составляющую гравитационной бибы
    // именно этого приёмника
    double getG(Cube &cu);
};

#endif // RECEIVER_H
