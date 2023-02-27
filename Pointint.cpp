#include "Pointint.h"
//generic point class containing an x and y value pair

    Pointint::Pointint(std::vector<int> coords)
    {
        this->coords=coords;
        this->N=coords.size();
    }

int Pointint::getIthCoordinate(int i)
{
    return this->coords[i];
}

int Pointint::getDims()
{
    return this->N;
}

//check
double Pointint::distanceTo(Pointint *p2)
{
    int sum=0;
    for(int i=0;i<this->coords.size();i++)
    {
        sum+=sqrt(pow(this->coords[i]-p2->coords[i],2));
    }
    return sum;
}

void Pointint::print()
{
    for(int i=0;i<this->N;i++)
    {
    std::cout<<this->getIthCoordinate(i)<<std::endl;
    }
}