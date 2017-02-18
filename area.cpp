#include "area.h"

double area::calcDensity(std::vector<subdomain> subs, cube cu)
{
    double p = 0;
    double volume = cu.getMes();
    double cutXmin, cutXmax, subX = 0;
    double cutYmin, cutYmax, subY = 0;
    double cutZmin, cutZmax, subZ = 0;
    if((cu.coords.x() == 0) && (cu.coords.y() == 0) && (cu.coords.z() == 0))
        p = p;
    for(size_t i = 0; i < subs.size(); ++i)
    {
        if(subs[i].xMin >= cu.nodes[1].x())
            continue;
        if(subs[i].xMax <= cu.nodes[0].x())
            continue;
        if(subs[i].yMin >= cu.nodes[2].y())
            continue;
        if(subs[i].yMax <= cu.nodes[0].y())
            continue;
        if(subs[i].zMin >= cu.nodes[4].z())
            continue;
        if(subs[i].zMax <= cu.nodes[0].z())
            continue;

        cutXmin = subs[i].xMin - cu.nodes[0].x();
        cutXmax = cu.nodes[1].x() - subs[i].xMax;
        if(cutXmin > 0) subX += cutXmin;
        if(cutXmax > 0) subX += cutXmax;
        subX = cu.nodes[1].x() - cu.nodes[0].x() - subX;

        cutYmin = subs[i].yMin - cu.nodes[0].y();
        cutYmax = cu.nodes[2].y() - subs[i].yMax;
        if(cutYmin > 0) subY += cutYmin;
        if(cutYmax > 0) subY += cutYmax;
        subY = cu.nodes[2].y() - cu.nodes[0].y() - subY;

        cutZmin = subs[i].zMin - cu.nodes[0].z();
        cutZmax = cu.nodes[4].z() - subs[i].zMax;
        if(cutZmin > 0) subZ += cutZmin;
        if(cutZmax > 0) subZ += cutZmax;
        subZ = cu.nodes[4].z() - cu.nodes[0].z() - subZ;
        if(subX == 0)
            continue;
        if(subY == 0)
            continue;
        if(subZ == 0)
            continue;
        p += ((subX * subY * subZ) / volume) * subs[i].density;
    }
    if(p > 20)
        p = p;
    return p;
}

void area::setNewP(vector<double> p)
{
    for(int i = 0; i < p.size(); ++i)
    {
        cubes[i].setDensity(p[i]);
    }
}

float area::getColor(cube cu)
{
    if(maxDensity == minDensity)
        return 0.5f;
    double temp = cu.getDensity() / (maxDensity - minDensity);
    if(temp == avgDensity)
        return 0.5f;
    return 1 - temp;
}
