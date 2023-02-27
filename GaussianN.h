#ifndef _GAUSSIANN_H_
#define _GAUSSIANN_H_
#include "Function.h"
#include "math.h"


//for testing purposes, multidimensional gaussian
class GaussianN : public Function
{
    private:
    int N;
    double a;
    double rho;
    double p;
    double theta;
    std::vector<double> displacements;

    //type2
    double aa;
    double cc;
    double bb;
    double normConst;

    int type;

    public:
    GaussianN();
    //type 2
    GaussianN(double a, double rho, double p, double theta, std::vector<double> displacements, int N, int dummy);
    
    //type 1
    GaussianN(double a,double rho, double p, double theta, std::vector<double> displacements, int N);
    double value(std::vector<double> inputs);
    void setNormConstant(double norm);
    double getNormConstant();

};

#endif