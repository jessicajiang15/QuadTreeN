#ifndef _POINT_H
#define _POINT_H 1
#include "math.h"
#include <vector>
#include <iostream>

//generic point class containing an x and y value pair
class Point
{
    private:
    int N;
    std::vector<double> coords;

    public:
    Point(std::vector<double> coords);
    Point(std::vector<double> coords, int N);
    double getIthCoordinate(int i);
    int getDims();
    /**
     * Returns the euclidean distance between this point and p2.
     * */
    double distanceTo(Point *p2);
    void print();
    std::vector<double> getCoords();
    void setCoord(int i, double val);
};
#endif