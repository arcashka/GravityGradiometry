#include "subdomain.h"

subdomain::subdomain()
{

}

bool subdomain::isInside(QVector3D a) {
    return a.x() > xMin && a.x() < xMax &&
           a.y() > yMin && a.y() < yMax &&
           a.z() > zMin && a.z() < zMax;
}

std::istream & operator >> (std::istream & is, subdomain & a) {
    is >> a.xMin >> a.xMax >> a.yMin >> a.yMax >> a.zMin >> a.zMax >> a.density;
    return is;
}
