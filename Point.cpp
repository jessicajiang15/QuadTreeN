#include "Point.h"
//generic point class containing an x and y value pair

    Point::Point(std::vector<double> coords)
    {
        //std::cout<<"yo~!"<<this->coords.size()<<std::endl;
        //std::cout<<"yo~!"<<coords.size()<<std::endl;
        this->coords=coords;
        //std::cout<<"yo~!"<<this->coords.size()<<std::endl;
        this->N=coords.size();
    }

double Point::getIthCoordinate(int i)
{
    return this->coords[i];
}

int Point::getDims()
{
    return this->N;
}

//check
double Point::distanceTo(Point *p2)
{
    int sum=0;
    for(int i=0;i<this->coords.size();i++)
    {
        sum+=sqrt(pow(this->coords[i]-p2->coords[i],2));
    }
    return sum;
}

void Point::print()
{
    for(int i=0;i<this->N;i++)
    {
        std::cout<<this->getIthCoordinate(i)<<std::endl;
    }
}
std::vector<double> Point::getCoords()
{
    return this->coords;
}

void Point::setCoord(int i, double val)
{
    this->coords[i]=val;
}