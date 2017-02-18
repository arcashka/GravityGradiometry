#include "inversetask.h"
#include <cmath>


inverseTask::inverseTask()
{

}



void inverseTask::getA(vector<cube> cu, vector<receiver> receivers)
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



void inverseTask::getb(vector<cube> cu, vector<receiver> receivers)
{
    size_t size = cu.size();
    b.resize(size, 0);

    for(size_t i = 0; i < receivers.size(); ++i)
        for(size_t q = 0; q < size; ++q)
            b[q] += receivers[i].getG(cu[q]) * receivers[i].grav;
}



vector< double > inverseTask::execInverseTask(vector<cube> cu, vector<receiver> receivers)
{
    getA(cu, receivers);
    getb(cu, receivers);
    toLU();
    findP();
    return p;
}



double inverseTask::getFunc(vector<cube> cu, vector<receiver> receivers)
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





vector< double > inverseTask::execWithRegular(
        vector<cube> cu, vector<receiver> receivers,
        double alpha, double gamma,
        double percentage, double gammaD, int& itt)
{
    itt = 0;
    initAlphaGamma(alpha, gamma, cu.size(), gammaD);
    double func;    // функционал
    execInverseTask(cu, receivers);
    func = getFunc(cu, receivers);


    do
    {
        if(!changeGamma(cu))
            break;
        applyGamma(cu);
        toLU();
        findP();
        itt++;
    }
    while(checkForOver(percentage, func, cu, receivers));
    return p;
}


bool inverseTask::checkCubeForRegular(vector<cube>& cu, cube& oneCU)
{
    double tempDiff = 0;
    size_t count = 0;

    for(size_t i = 0; i < 6; ++i)
    {
        if(oneCU.neighbours[i] != -1)
        {
            tempDiff += abs(oneCU.getDensity()
                            - cu[oneCU.neighbours[i]].getDensity());
            ++count;
        }
    }
    tempDiff /= count;
    if(tempDiff > (5 * oneCU.getDensity()))
        return true;
    else
        return false;
}


bool inverseTask::changeGamma(vector<cube> &cu)
{
    bool changed = false;
    for(size_t i = 0; i < cu.size(); ++i)
    {
        if(checkCubeForRegular(cu, cu[i]))
        {
            changed = true;
            gamma[i] += gammaD;
        }
    }
    return true;
}


void inverseTask::initAlphaGamma(double alpha, double gamma, size_t gammaSize, double gammaD)
{
    inverseTask::alpha = alpha;
    inverseTask::gammaD = gammaD;
    inverseTask::gamma.resize(gammaSize, gamma);
}


void inverseTask::findP()
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
    for(int i = size - 1; i >= 0; --i)
    {
        temp = 0;
        for(size_t k = size - 1; k > i; --k)
            temp += p[k] * Afact[i][k];
        p[i] = (bw[i] - temp) / Afact[i][i];
    }
}



double inverseTask::l(int i, int j)
{
    double temp = 0;
    for(size_t k = 0; k < i; ++k)
        temp -= Afact[j][k] * Afact[k][i];
    temp += Afact[j][i];
    temp /= Afact[i][i];
    return temp;
}



double inverseTask::u(int i, int j)
{
    double temp = 0;
    for(size_t k = 0; k < i; ++k)
        temp -= Afact[i][k] * Afact[k][j];
    temp += Afact[i][j];
    return temp;
}



void inverseTask::applyGamma(vector<cube> cu)
{
    for(size_t i = 0; i < cu.size(); ++i)
    {
        double sum = 0;
        size_t count = 0;
        for(size_t j = 0; j < 6; ++j)
        {
            if(cu[i].neighbours[j] != -1)
            {
                A[i][cu[i].neighbours[j]] -= gamma[i] + gamma[cu[i].neighbours[j]];
                ++count;
                sum += gamma[cu[i].neighbours[j]];
            }
        }
        A[i][i] += gamma[i] * count + sum + alpha;
    }
}


bool inverseTask::checkForOver(double percentage,
                               double func, vector<cube> &cu,
                               vector<receiver> &receivers)
{
    double tempFunc = getFunc(cu, receivers);
    if((tempFunc - func) > func / 100.f * percentage)
        return false;
    else
        return true;
}


void inverseTask::toLU()
{
    size_t size = A.size();
//    Afact.resize(size);
//    for(size_t i = 0; i < size; ++i)
//        Afact[i].resize(size);

    Afact = A;
    for(size_t i = 0; i < size; ++i)
        for(size_t j = i; j < size; ++j)
        {
            Afact[i][j] = u(i,j);
            if(i != j)
                Afact[j][i] = l(i,j);
        }
}



