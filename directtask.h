#ifndef DIRECTTASK_H
#define DIRECTTASK_H
#include <vector>
#include "receiver.h"
#include "cube.h"

        //      все приёмники располагаются на поверхности
        //      в одной плоскости.
        //      Расположены они равномерно.
class directTask
{
public:
    void execDirectTask(std::vector<cube> cubes, double xMin, double xMax, double yMin, double yMax, double zMax);
    directTask();
         //      количество разбиений по X и по Y
    int numX, numY;
    ~directTask();
    std::vector<receiver> receivers;

};

#endif // DIRECTTASK_H
