#ifndef _RectangleN_H
#define _RectangleN_H 1
#include "Point.h"
#include <vector>
#include "Function.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GraphicsMechanics.h"
#include "string.h"
#include <iomanip>

//RectangleN

class RectangleN
{
    private:
    /**
     * Cartesian coordinate of the bottom left corner of the RectangleN.
     * */
    Point *point;
    /**
     * 
     **/
    int N;

    //list of lengths. total of N
    std::vector<double> dims;
    /**
     * The SFML Rectangle object for graphics.
     * */
    sf::RectangleShape* rect;

    public:
    /**
     * constructors
     * */
    RectangleN(Point *corner, int N, std::vector<double> dims);
    /**
     * Destructor
     * */
    virtual ~RectangleN()
    {
        delete point;

    }
    /**
     * Getter for vol of RectangleN. Necessary for approximate integral on RectangleN region
     * */
     double getVol();
     
    double getithInterval(int i);
    //gets ith coord of bottom left corner.
    double getithCoord(int i);

    double getCenterI(int i);

    Point* getPoint();
    
    /**
     * Integrates a function F over the region represented by this RectangleN.
     * Dummy function– I don't actually know how to incorporate integration
     * with this code yet. Will be implemented soon (if ever, currently using
     * approximation methods).
     * */
    double integrate(Function *F);
    /**
     * Returns a midpoint rectangular prism approximation of the integral
     * of a function F over the region represented by this RectangleN.
     * */
    double approx(Function *F);
    double approx(double **F);

    std::string toStringCoord();
    std::string toStringCoordBottomRight();
    std::string toStringCoordTopLeft();
    //draws the RectangleN
    void draw(sf::RenderWindow *window, int dim1, int dim2);
    /**
     * Creates a RectangleN with the given boundaries. The x values that define the RectangleN will lie
     * between maxX and minX (minX<x<maxX), and the y values that define the RectangleN will lie
     * between minY and maxY, so minY<y<maxY.
     * Its length will be |maxX-minX| and its width will be |maxY-minY|
     * */
    void createSfRectFromCartesian(double minX, double maxX, double minY, double maxY, int dim1, int dim2);
    /**
     * Gives a more accurate approximation of the integral by splitting up this RectangleN into an
     * accuracy x accuracy grid and evaluating the midpoint rectangular prism volume for each
     * little RectangleN, then adding them up.
     * */
    double getAccurateApprox(Function *F, int accuracy);
    void setColor(std::string s);
    int getN();
    //double integralGaussApprox(int MAX_ITERATIONS, Function *F, GaussianQuadrature* quadrature);
    Point* getMidPoint();
    
};
#endif