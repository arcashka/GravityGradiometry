#ifndef DIRECTTASK_H
#define DIRECTTASK_H
#include <vector>
#include "areaHeaders/receiver.h"
#include "areaHeaders/cube.h"
#include "areaHeaders/areaproperties.h"

// все приёмники располагаются на поверхности
// в одной плоскости.
// Расположены они равномерно.
class DirectTask
{
private:
    int numX, numY;
    std::vector<Receiver> receivers;
public:
    void execDirectTask(std::vector<Cube>& cubes, AreaProperties properties);
    DirectTask();
    ~DirectTask();

    // accessors
    int getNumX()                           { return numX; }
    int getNumY()                           { return numY; }
    Receiver getReceiver(int i)             { return receivers[i]; }
    std::vector< Receiver > getReceivers()  { return receivers; }

    // mutators
    void setNumX(int numX) { DirectTask::numX = numX; }
    void setNumY(int numY) { DirectTask::numY = numY; }
};

#endif // DIRECTTASK_H
