#include "CompTwoFunc.h"

    CompTwoFunc::CompTwoFunc(Function *initial, Function *final)
    {
        this->initial=initial;
        this->final=final;

    }

    double CompTwoFunc::value(std::vector<double> values)
    {
        return (initial->value(values)-final->value(values));
    }
