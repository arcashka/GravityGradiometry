#ifndef SUBDOMAIN_H
#define SUBDOMAIN_H
#include "areaHeaders/cube.h"
#include <fstream>

class Subdomain
{
private:
    double xMin, xMax;
    double yMin, yMax;
    double zMin, zMax;
                            // плотность
    double density;
public:

    // accessors
    double getXMin() { return xMin; }
    double getYMin() { return yMin; }
    double getZMin() { return zMin; }
    double getXMax() { return xMax; }
    double getYMax() { return yMax; }
    double getZMax() { return zMax; }

    double getDensity() { return density; }


                            // проверка на то, находится ли куб с центром в а
                            // в данной подобласти
    bool isInside(QVector3D a);
                            // ввод целой области через один оператор
    friend std::istream & operator >> (std::istream & is, Subdomain & a);
    Subdomain();
};

#endif // SUBDOMAIN_H
