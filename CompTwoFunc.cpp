#include "CompTwoFunc.h"

    CompTwoFunc::CompTwoFunc(Function *initial, Function *final)
    {
        this->initial=initial;
        this->final=final;

    }

    double CompTwoFunc::value(std::vector<double> values)
    {
        //std::cout<<"ss"<<std::endl;
       // std::cout<<initial->value(values)<<std::endl;
        //std::cout<<final->value(values)<<std::endl;
        //std::cout<<initial->value(values)-final->value(values)<<std::endl;
        return (initial->value(values)-final->value(values));
    }
