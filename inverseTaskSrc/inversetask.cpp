#include "inverseTaskHeaders/inversetask.h"
#include <cmath>


InverseTask::InverseTask()
{

}



void InverseTask::computeA(vector<Cube> &cu, vector<Receiver> &receivers)
{
    size_t size = cu.size();
    A.resize(size);
    for(size_t i = 0; i < size; ++i)
        A[i].resize(size, 0);

    for(size_t i = 0; i < receivers.size(); ++i)
    {
        for(size_t q = 0; q < size; ++q)
        {
            for(size_t s = 0; s < size; ++s)
            {
                A[q][s] += receivers[i].getG(cu[q]) * receivers[i].getG(cu[s]);
            }
        }
    }
}



void InverseTask::computeB(vector<Cube>& cu, vector<Receiver>& receivers)
{
    size_t size = cu.size();
    b.resize(size);

    for(size_t i = 0; i < receivers.size(); ++i)
        for(size_t q = 0; q < size; ++q)
            b[q] += receivers[i].getG(cu[q]) * receivers[i].grav;
}



vector< double > InverseTask::execInverseTask(vector<Cube> &cu, vector<Receiver> &receivers)
{
    computeA(cu, receivers);
    computeB(cu, receivers);
    toLU();
    computeP();
    return p;
}



double InverseTask::getFunc(vector<Cube> &cu, vector<Receiver> &receivers)
{
    double func = 0;
    for(size_t i = 0; i < receivers.size(); ++i)
    {
        double temp = 0;
        for(size_t k = 0; k < cu.size(); ++k)
        {
            temp += p[k] * receivers[i].getG(cu[k]);
        }
        func += (receivers[i].grav - temp) * (receivers[i].grav - temp);
    }
    return func;
}





vector< double > InverseTask::execWithRegular(vector<Cube>& cu, vector<Receiver>& receivers,
        InverseTaskProperties& properties, int& itt)
{
    itt = 0;
    initAlphaGamma(properties.alpha, properties.gamma, cu.size(), properties.gammaStep);
    double func;    // функционал
    execInverseTask(cu, receivers);
    func = getFunc(cu, receivers);


    do
    {
        if(!changeGamma(cu))
            break;
        applyGamma(cu);
        toLU();
        computeP();
        itt++;
    }
    while(checkForOver(properties.percentage, func, cu, receivers));
    return p;
}


bool InverseTask::checkCubeForRegular(vector<Cube>& cu, Cube& oneCU)
{
    double tempDiff = 0;
    int count = 0;

    for(int i = 0; i < 6; ++i)
    {
        if(oneCU.getNeighbour(i) != -1)
        {
            tempDiff += abs(oneCU.getDensity()
                            - cu[oneCU.getNeighbour(i)].getDensity());
            ++count;
        }
    }
    tempDiff /= count;
    if(tempDiff > (5 * oneCU.getDensity()))
        return true;
    else
        return false;
}


bool InverseTask::changeGamma(vector<Cube> &cu)
{
    bool changed = false;
    for(size_t i = 0; i < cu.size(); ++i)
    {
        if(checkCubeForRegular(cu, cu[i]))
        {
            changed = true;
            gamma[i] += gammaStep;
        }
    }
    return true;
}


void InverseTask::initAlphaGamma(double alpha, double gamma, size_t gammaSize, double gammaD)
{
    InverseTask::alpha = alpha;
    InverseTask::gammaStep = gammaD;
    InverseTask::gamma.resize(gammaSize, gamma);
}


void InverseTask::computeP()
{
    size_t size = b.size();
    vector< double > bw = b;
    p.resize(size);
    double temp;
    // L
    for(size_t i = 0; i < size; ++i)
    {
        temp = 0;
        for(size_t k = 0; k < i; ++k)
            temp += bw[k] * Afact[i][k];
        bw[i] = bw[i] - temp;
    }

    // U
    for(size_t i = size - 1; i >= 0; --i)
    {
        temp = 0;
        for(size_t k = size - 1; k > i; --k)
            temp += p[k] * Afact[i][k];
        p[i] = (bw[i] - temp) / Afact[i][i];
    }
}



double InverseTask::l(int i, int j)
{
    double temp = 0;
    for(size_t k = 0; k < i; ++k)
        temp -= Afact[j][k] * Afact[k][i];
    temp += Afact[j][i];
    temp /= Afact[i][i];
    return temp;
}



double InverseTask::u(int i, int j)
{
    double temp = 0;
    for(size_t k = 0; k < i; ++k)
        temp -= Afact[i][k] * Afact[k][j];
    temp += Afact[i][j];
    return temp;
}



void InverseTask::applyGamma(vector<Cube> &cu)
{
    for(size_t i = 0; i < cu.size(); ++i)
    {
        double sum = 0;
        int count = 0;
        for(int j = 0; j < 6; ++j)
        {
            if(cu[i].getNeighbour(j) != -1)
            {
                A[i][cu[i].getNeighbour(j)] -= gamma[i] + gamma[cu[i].getNeighbour(j)];
                ++count;
                sum += gamma[cu[i].getNeighbour(j)];
            }
        }
        A[i][i] += gamma[i] * count + sum + alpha;
    }
}


bool InverseTask::checkForOver(double percentage,
                               double func, vector<Cube> &cu,
                               vector<Receiver> &receivers)
{
    double tempFunc = getFunc(cu, receivers);
    if((tempFunc - func) > func / 100.f * percentage)
        return false;
    else
        return true;
}


void InverseTask::toLU()
{
    size_t size = A.size();
//    Afact.resize(size);
//    for(size_t i = 0; i < size; ++i)
//        Afact[i].resize(size);

    Afact = A;
    for(int i = 0; i < size; ++i)
        for(int j = i; j < size; ++j)
        {
            Afact[i][j] = u(i,j);
            if(i != j)
                Afact[j][i] = l(i,j);
        }
}



