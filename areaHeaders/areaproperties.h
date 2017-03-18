#ifndef AREAPROPERTIES_H
#define AREAPROPERTIES_H

struct AreaProperties {
    // Количество разбиений по каждой из координат
    int xNum, yNum, zNum;
    // МИнимальные - максимальные значения по всем координатам
    double xMin, xMax, yMin, yMax, zMin, zMax;
    // Средняя, минимальная и максимальная плотности по области
    double avgDensity;
    double maxDensity = 0;
    double minDensity = 0;
};

#endif // AREAPROPERTIES_H
