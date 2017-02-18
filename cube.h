#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <QVector3D>

class cube
{
private:
    double mes;                     // объём
    double density;                 // плотность
    QVector3D center;               // нужен, чтобы смотреть попал он в подобласть или нет
public:
    bool gaussDid = false;
                                    // индексация по каждой из координат
                                    // как, если бы у нас был трёхмерный вектор
    QVector3D coords;
                                    // 8 точек задают куб
    std::vector<QVector3D> nodes;


    void breakForGauss();


    std::vector< double > gaussWeights;
    std::vector< QVector3D > gaussPoints;
    double jacobian;
    int neighbours[6];


    //                      get
    double getDensity() {return density;}
    double getMes() {return mes;}
                                    // создаёт куб по одной точке и шагам по каждой из координат
    cube(double x, double y, double z, double xmin, double ymin, double zmin, double hx, double hy, double hz);
    QVector3D getCenter() {return center;}



    //                      set
    void setCenter(QVector3D newCenter) {center = newCenter;}
    void setDensity(double newDensity) {density = newDensity;}
    void setMes(double newMes) {mes = newMes;}
};

#endif // CUBE_H
