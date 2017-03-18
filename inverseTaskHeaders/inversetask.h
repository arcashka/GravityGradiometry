#ifndef INVERSETASK_H
#define INVERSETASK_H
#include "directTaskHeaders/directtask.h"
#include "inverseTaskHeaders/inversetaskproperties.h"
using namespace std;

class InverseTask
{
public:
    vector< double > execInverseTask(vector< Cube >& cu, vector< Receiver >& receivers);
    vector< double > execWithRegular(vector< Cube >& cu, vector< Receiver >& receivers,
                                     InverseTaskProperties& properties, int &itt);
    InverseTask();
private:

    // вектор плотности
    vector<double> p;

    // матрица А
    vector< vector< double > > A;

    // фактаризованная матрица А
    vector< vector< double > > Afact;

    // вектор правой части
    vector< double > b;

    double alpha;

    vector< double > gamma;

    // проверка, нужно ли увеличивать гамму для данного куба
    bool checkCubeForRegular(vector< Cube >& cu, Cube &oneCU);

    // вычислить матрицу А
    void computeA(vector< Cube >& cu, vector< Receiver >& receivers);

    // вычислить вектор правой части
    void computeB(vector< Cube >& cu, vector< Receiver >& receivers);

    // функции для факторизации
    double u(int i, int j);
    double l(int i, int j);

    // факторизует матрицу А
    void toLU();

    // решает слау
    void computeP();

    // меняет матрицу А в соответствии с вектором гамма
    void applyGamma(vector< Cube >& cu);

    // проходит по всем кубам и увеличивает гамму если нужно
    bool changeGamma(vector< Cube >& cu);

    // возвращает значение функционала
    double getFunc(vector< Cube >& cu, vector< Receiver >& receivers);

    // инициализация параметров регуляризации
    void initAlphaGamma(double alpha, double gamma, size_t gammaSize, double gammaStep);

    // проверка, нужно ли продолжать регуляризацию
    bool checkForOver(double percentage, double func,
                      vector< Cube >& cu,
                      vector< Receiver >& receivers);

    double gammaStep = 0.5;
};

#endif // INVERSETASK_H
