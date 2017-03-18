#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <QVector3D>
#include <areaHeaders/areaproperties.h>
#include "Utility/Index3d.h"

class Cube
{
private:
    // объём
    double mes;

    // плотность
    double density;

    // нужен, чтобы смотреть попал он в подобласть или нет
    QVector3D center;

    // раскладываем ли мы этот куб на точки гаусса
    bool gaussDid = false;

    // индексация по каждой из координат
    // как, если бы у нас был трёхмерный вектор
    Index3D index;

    // 8 точек задают куб
    std::vector<QVector3D> nodes;

    // веса гаусса
    std::vector< double > gaussWeights;

    // координаты точек гаусса
    std::vector< QVector3D > gaussPoints;

    // якобиан
    double jacobian;

    // индексы соседей этого куба
    int neighbours[6];

public:
    // accessors
    double      getDensity()            { return density; }
    double      getMes()                { return mes; }
    QVector3D&  getCenter()             { return center; }
    bool        getGaussDid()           { return gaussDid; }
    QVector3D&  getGaussPoint(int i)    { return gaussPoints[i]; }
    double      getGaussWeight(int i)   { return gaussWeights[i]; }
    Index3D&    getIndex()              { return index; }
    QVector3D&  getNode(int i)          { return nodes[i]; }
    double      getJacobian()           { return jacobian; }
    int         getNeighbour(int i)     { return neighbours[i]; }


    // mutators
    void setCenter(QVector3D& newCenter)    { center = newCenter; }
    void setDensity(double newDensity)      { density = newDensity; }
    void setMes(double newMes)              { mes = newMes; }

    // создаёт куб по одной точке и шагам по каждой из координат
    Cube(QVector3D a, AreaProperties& properties, QVector3D ha);

    // раскладываем куб на точки гаусса
    void breakForGauss();
};

#endif // CUBE_H
