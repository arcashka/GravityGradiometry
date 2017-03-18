#ifndef AREA_H
#define AREA_H
#include "areaHeaders/subdomain.h"
#include "areaHeaders/areaproperties.h"
#include "directTaskHeaders/directtask.h"
#include "inverseTaskHeaders/inversetask.h"
#include "inverseTaskHeaders/inversetaskproperties.h"
#include <limits>

using namespace std;

class Area
{
private:
    vector<Cube> ar.getCubes();
    DirectTask dTask;
    InverseTask iTask;

    double calcDensity(vector<Subdomain> subs, Cube cu);

    // Дополнительные данные
    AreaProperties properties;

public:
    Area();
    void setNewP(vector< double > p);
    vector<Cube>& getCubes() { return ar.getCubes(); }
    void executeDirectTask(int numX, int numY);
    vector< double >& executeInverseTaskRegularisation(InverseTaskProperties& properties, int &itt);
    vector< double >& executeInverseTask();

    template<typename T>
    bool generateFromStream(T & ifs)
    {
        maxDensity = 0;
        minDensity = std::numeric_limits<double>::max();
        avgDensity = 0;
        ar.getCubes().clear();
        std::vector<Subdomain> subs;
        double tempDensity;

        // параметры для всей расчётной области
        // минимальные / максимальные значения по каждой из координат
        ifs >> properties.xMin >> properties.xMax
                >> properties.yMin >> properties.yMax
                >> properties.zMin >> properties.zMax;

        // количество разбиений по каждой из координат
        ifs >> properties.xNum >> properties.yNum >> properties.zNum;

        // количество разных подобластей
        int incNum;
        ifs >> incNum;
        // записываем эти области
        subs.resize(incNum);
        for(int i = 0; i < incNum; ++i)
            ifs >> subs[i];
        int ittDens = 0;

        // посчитали величину шага по каждой координате
        double hx = (properties.xMax - properties.xMin) / static_cast<double>(properties.xNum),
               hy = (properties.yMax - properties.yMin) / static_cast<double>(properties.yNum),
               hz = (properties.zMax - properties.zMin) / static_cast<double>(properties.zNum);

        // добавляем все кубы
        int numb = 0;
        for(int i = 0; i < properties.xNum; ++i)
        {

            double xCurr = properties.xMin + hx * static_cast<double>(i);
            for(int j = 0; j < properties.yNum; ++j)
            {

                double yCurr = properties.yMin + hy * static_cast<double>(j);
                for(int k = 0; k < properties.zNum; ++k)
                {

                    tempDensity = 0;
                    double zCurr = properties.zMin + hz * static_cast<double>(k);
                    Cube temp = Cube(xCurr, yCurr, zCurr, xMin, yMin, zMin, hx, hy, hz);
                    tempDensity = calcDensity(subs, temp);
                    temp.setDensity(tempDensity);
                    if(tempDensity > 1E-1)
                    {
                        avgDensity += tempDensity;
                        ++ittDens;
                    }
                    if(tempDensity > maxDensity)
                        maxDensity = tempDensity;
                    if(tempDensity < minDensity)
                        minDensity = tempDensity;

                    //          соседи
                    if(i > 0)           temp.neighbours[0] = numb - yNum * zNum;        // левый
                    if(j > 0)           temp.neighbours[1] = numb - zNum;               // ближний
                    if(k > 0)           temp.neighbours[2] = numb - 1;                  // нижний
                    if(k < zNum - 1)    temp.neighbours[3] = numb + 1;                  // верхний
                    if(j < yNum - 1)    temp.neighbours[4] = numb + zNum;               // дальний
                    if(i < xNum - 1)    temp.neighbours[5] = numb + yNum * zNum;        // правый
                    ar.getCubes().push_back(temp);
                    ++numb;

                }

            }

        }
        avgDensity /= ittDens;
        return true;

    }
};

#endif // AREA_H
