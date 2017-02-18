#ifndef AREA_H
#define AREA_H
#include "subdomain.h"
#include "directtask.h"
#include "inversetask.h"
#include <limits>

class area
{
private:                    // количество разбиений по каждой из координат
    double calcDensity(std::vector<subdomain> subs, cube cu);
public:
    size_t xNum, yNum, zNum;
    double xMin, xMax, yMin, yMax, zMin, zMax;
    directTask dTask;
    inverseTask iTask;
    void setNewP(vector< double > p);
    float getColor(cube cu);
                            // кубы, что в ней
    std::vector<cube> cubes;
                            // переменная для widget3d
    bool drawLines = true;
    bool gaussPointsDraw = false;
                            // средняя плотность, чтобы раскрашивать
    double avgDensity;
    double maxDensity = 0;
    double minDensity = 0;

                            // выполнение прямой задачи
                            // строится сетка из numX на numY гравиметров
    template<typename T>
    bool generateFromStream(T & ifs)
    {
        maxDensity = 0;
        minDensity = std::numeric_limits<double>::max();
        avgDensity = 0;
        cubes.clear();
        std::vector<subdomain> subs;
        double tempDensity;


        // параметры для всей расчётной области
        // минимальные / максимальные значения по каждой из координат
        ifs >> xMin >> xMax >> yMin >> yMax >> zMin >> zMax;

        // количество разбиений по каждой из координат
        ifs >> xNum >> yNum >> zNum;




        // количество разных подобластей
        size_t incNum;
        ifs >> incNum;
        // записываем эти области
        subs.resize(incNum);
        for(int i = 0; i < incNum; ++i)
            ifs >> subs[i];
        int ittDens = 0;


        // посчитали величину шага по каждой координате
        double hx = (xMax - xMin) / static_cast<double>(xNum),
               hy = (yMax - yMin) / static_cast<double>(yNum),
               hz = (zMax - zMin) / static_cast<double>(zNum);



        // добавляем все кубы
        size_t numb = 0;
        for(size_t i = 0; i < xNum; ++i)
        {

            double xCurr = xMin + hx * static_cast<double>(i);
            for(size_t j = 0; j < yNum; ++j)
            {

                double yCurr = yMin + hy * static_cast<double>(j);
                for(size_t k = 0; k < zNum; ++k)
                {

                    tempDensity = 0;
                    double zCurr = zMin + hz * static_cast<double>(k);
                    cube temp = cube(xCurr, yCurr, zCurr, xMin, yMin, zMin, hx, hy, hz);
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
                    if(i < xNum - 1)    temp.neighbours[5] = numb + yNum * zNum;
                    cubes.push_back(temp);
                    ++numb;

                }

            }

        }
        avgDensity /= ittDens;
        return true;

    }
};

#endif // AREA_H
