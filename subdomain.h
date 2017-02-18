#ifndef SUBDOMAIN_H
#define SUBDOMAIN_H
#include "cube.h"
#include <fstream>

class subdomain
{
public:
    double xMin, xMax;
    double yMin, yMax;
    double zMin, zMax;
                            // плотность
    double density;
                            // проверка на то, находится ли куб с центром в а
                            // в данной подобласти
    bool isInside(QVector3D a);
                            // ввод целой области через один оператор
    friend std::istream & operator >> (std::istream & is, subdomain & a);
    subdomain();
};

#endif // SUBDOMAIN_H
