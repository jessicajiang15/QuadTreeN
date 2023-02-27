#ifndef _POINTINT_H
#define _POINTINT_H 1
#include "math.h"
#include <vector>
#include <iostream>

//generic point class containing an x and y value pair
class Pointint
{
    private:
    int N;
    std::vector<int> coords;

    public:
    Pointint(std::vector<int> coords);
    Pointint(std::vector<int> coords, int N);
    int getIthCoordinate(int i);
    int getDims();
    /**
     * Returns the euclidean distance between this point and p2.
     * */
    double distanceTo(Pointint *p2);

    void print();
};
#endif