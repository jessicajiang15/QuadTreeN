#ifndef _COMPTWOFUNC_H
#define _COMPTWOFUNC_H
#include "Function.h"

class CompTwoFunc : public Function
{

    private:
    //initial-final
    Function *initial;
    Function *final;

    public:
    CompTwoFunc(Function *initial, Function *final);
    double value(std::vector<double> values) override;
};

#endif