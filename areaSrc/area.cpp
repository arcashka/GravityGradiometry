#include "areaHeaders/area.h"

double Area::calcDensity(std::vector<Subdomain> subs, Cube cu)
{
    double p = 0;
    double volume = cu.getMes();
    double cutXmin, cutXmax, subX = 0;
    double cutYmin, cutYmax, subY = 0;
    double cutZmin, cutZmax, subZ = 0;
    if((cu.getIndex().geti() == 0) && (cu.getIndex().getj() == 0) && (cu.getIndex().getk() == 0))
        p = p;
    for(size_t i = 0; i < subs.size(); ++i)
    {
        if(subs[i].getXMin() >= cu.getNode(1).x())
            continue;
        if(subs[i].getXMax() <= cu.getNode(0).x())
            continue;
        if(subs[i].getYMin() >= cu.getNode(2).y())
            continue;
        if(subs[i].getYMax() <= cu.getNode(0).y())
            continue;
        if(subs[i].getZMin() >= cu.getNode(4).z())
            continue;
        if(subs[i].getZMax() <= cu.getNode(0).z())
            continue;

        cutXmin = subs[i].getXMin() - cu.getNode(0).x();
        cutXmax = cu.getNode(1).x() - subs[i].getXMax();
        if(cutXmin > 0) subX += cutXmin;
        if(cutXmax > 0) subX += cutXmax;
        subX = cu.getNode(1).x() - cu.getNode(0).x() - subX;

        cutYmin = subs[i].getYMin() - cu.getNode(0).y();
        cutYmax = cu.getNode(2).y() - subs[i].getYMax();
        if(cutYmin > 0) subY += cutYmin;
        if(cutYmax > 0) subY += cutYmax;
        subY = cu.getNode(2).y() - cu.getNode(0).y() - subY;

        cutZmin = subs[i].getZMin() - cu.getNode(0).z();
        cutZmax = cu.getNode(4).z() - subs[i].getZMax();
        if(cutZmin > 0) subZ += cutZmin;
        if(cutZmax > 0) subZ += cutZmax;
        subZ = cu.getNode(4).z() - cu.getNode(0).z() - subZ;
        if(subX == 0)
            continue;
        if(subY == 0)
            continue;
        if(subZ == 0)
            continue;
        p += ((subX * subY * subZ) / volume) * subs[i].getDensity();
    }
    return p;
}

void Area::setNewP(vector<double> p)
{
    for(int i = 0; i < p.size(); ++i)
    {
        ar.getCubes()[i].setDensity(p[i]);
    }
}


vector< double >& Area::executeInverseTaskRegularisation(InverseTaskProperties &properties, int &itt)
{
    return iTask.execWithRegular(ar.getCubes(), dTask.getReceivers(), properties, itt);
}

vector< double >& Area::executeInverseTask()
{
    return iTask.execInverseTask(ar.getCubes(), dTask.getReceivers());
}

void Area::executeDirectTask(int numX, int numY) {
    dTask.setNumX(numX);
    dTask.setNumY(numY);
    dTask.execDirectTask(ar.getCubes(), properties);
}

Area::Area() {

}

//float Area::getColor(Cube cu)
//{
//    if(maxDensity == minDensity)
//        return 0.5f;
//    double temp = cu.getDensity() / (maxDensity - minDensity);
//    if(temp == avgDensity)
//        return 0.5f;
//    return 1 - temp;
//}
