#ifndef INVERSETASK_H
#define INVERSETASK_H
#include "directtask.h"
using namespace std;

class inverseTask
{
public:
    inverseTask();



    vector<double> p;
    vector< vector< double > > A;
    vector< vector< double > > Afact;
    vector< double > b;
    double alpha;
    vector< double > gamma;


    vector< double > execInverseTask(vector< cube > cu, vector< receiver > receivers);
    vector< double > execWithRegular(vector< cube > cu, vector< receiver > receivers,
                                     double alpha, double gamma,
                                     double percentage, double gammaD, int &itt);
private:
    bool checkCubeForRegular(vector< cube >& cu, cube &oneCU);
    void getA(vector< cube > cu, vector< receiver > receivers);
    void getb(vector< cube > cu, vector< receiver > receivers);
    double u(int i, int j);
    double l(int i, int j);
    void toLU();
    void findP();
    void applyGamma(vector< cube > cu);
    bool changeGamma(vector< cube >& cu);
    double getFunc(vector< cube > cu, vector< receiver > receivers);
    void initAlphaGamma(double alpha, double gamma, size_t gammaSize, double gammaD);
    bool checkForOver(double percentage, double func,
                      vector< cube >& cu,
                      vector< receiver >& receivers);
    double gammaD = 0.5;
};

#endif // INVERSETASK_H
