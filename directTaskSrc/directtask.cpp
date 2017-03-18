#include "directTaskHeaders/directtask.h"
#include <QDebug>
#include <QString>

void DirectTask::execDirectTask(std::vector<Cube>& cubes, AreaProperties properties)
{
    for(int i = 0; i < cubes.size(); ++i)
        if(cubes[i].getNode(4).z() == properties.zMax)
        {
            double temp = (cubes[i].getNode(1).x() - cubes[i].getNode(0).x()) *
                    (cubes[i].getNode(2).y() - cubes[i].getNode(0).y());
            // TODO переделать
            // вообще поиграться, чтобы он хоть когда-нибудь их ломал
            if(temp > 4 * (properties.xMax - properties.xMin) /
                   numX * (properties.yMax - properties.yMin) * numY)
                cubes[i].breakForGauss();
        }


    DirectTask::receivers.resize(numX * numY);
    double z = properties.zMax;
    double hx = (properties.xMax - properties.xMin) / numX;
    double hy = (properties.yMax - properties.yMin) / numY;

    // Создаём всё приёмники
    for(int i = 0; i < numY; ++i)
        for(int j = 0; j < numX; ++j)
            receivers[j + numX * i] = Receiver(hx * i + properties.xMin, hy * j + properties.yMin, z);

    // Заполняем грав.
    for(int i = 0; i < receivers.size(); ++i)
        for(int j = 0; j < cubes.size(); ++j)
            receivers[i].grav += cubes[j].getDensity() * receivers[i].getG(cubes[j]);
}

DirectTask::~DirectTask()
{

}

DirectTask::DirectTask()
{

}
