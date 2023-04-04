#include "InterpolatedFunction.h"


InterpolatedFunction::InterpolatedFunction(SPLINTER::DataTable samples, int dim, int degree, bool p)
{

    this->degree=degree;
    this->dims=dim;
    this->samples=samples;

    if(p)
    {

    this->bspline.push_back(SPLINTER::BSpline::Builder(this->samples).degree(this->degree).build());
    }
    else
    {

        this->bspline.push_back(SPLINTER::BSpline::Builder(samples)
            .degree(this->degree)
            .smoothing(SPLINTER::BSpline::Smoothing::PSPLINE)
            .alpha(0.03)
            .build());
    }
    
}

double InterpolatedFunction::value(std::vector<double> values)
{
    SPLINTER::DenseVector temp(values.size());

    for(int i=0;i<values.size();i++)
    {
        temp(i)=values[i];
    }
    return bspline[0].eval(temp);
}