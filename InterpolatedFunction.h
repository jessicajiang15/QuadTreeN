#ifndef _INTERPOLATEDFUNCTION_H_
#define _INTERPOLATEDFUNCTION_H_
#include "Function.h"

class InterpolatedFunction : public Function
{
    private:
        //data table to store points of data
        SPLINTER::DataTable samples;
        std::vector<double> widths;
        std::vector<double> maxes;
        std::vector<double> mins;
        int dims;
        //spline degree
        int degree;
        std::vector<SPLINTER::BSpline> bspline;
        //SPLINTER::BSpline bspline = nullptr;

    public:
    InterpolatedFunction(SPLINTER::DataTable samples, int dim, int degree, bool p);
    
    double value(std::vector<double> values) override;
};

#endif