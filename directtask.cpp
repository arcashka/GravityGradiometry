#include "directtask.h"
#include <QDebug>
#include <QString>

void directTask::execDirectTask(std::vector<cube> cubes, double xMin, double xMax, double yMin, double yMax, double zMax)
{
    for(size_t i = 0; i < cubes.size(); ++i)
        if(cubes[i].nodes[4].z() == zMax)
        {
            double temp = (cubes[i].nodes[1].x() - cubes[i].nodes[0].x()) *
                    (cubes[i].nodes[2].y() - cubes[i].nodes[0].y());
            if(temp > 4 * (xMax - xMin) / numX * (yMax - yMin) * numY)
                cubes[i].breakForGauss();
        }


    directTask::receivers.resize(numX * numY);
    double z = zMax;
    double hx = (xMax - xMin) / numX;
    double hy = (yMax - yMin) / numY;

    for(size_t i = 0; i < numY; ++i)
        for(size_t j = 0; j < numX; ++j)
            receivers[j + numX * i] = receiver(hx * i + xMin, hy * j + yMin, z);

    for(size_t i = 0; i < receivers.size(); ++i)
        for(size_t j = 0; j < cubes.size(); ++j)
            receivers[i].grav += cubes[j].getDensity() * receivers[i].getG(cubes[j]);
}

directTask::~directTask()
{

}

directTask::directTask()
{

}
