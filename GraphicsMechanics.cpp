#include "GraphicsMechanics.h"

Point *GraphicsMechanics::convertFromCartesian(double minX, double maxX, double minY, double maxY, Point *p, int dim1, int dim2)
{
    double intervalX = maxX - minX;
    double xScale = (double)WINDOW_WIDTH / intervalX;
    double intervalY = maxY - minY;
    double yScale = (double)WINDOW_HEIGHT / intervalY;
    double xShiftCart = -minX;
    double xShiftSf = xShiftCart * xScale;
    double yShiftCart = -minY;
    double yShiftSf = yShiftCart * yScale;
    double x = p->getIthCoordinate(dim1);
    double y = p->getIthCoordinate(dim2);
    double newX = x * xScale + xShiftSf;
    double newY = (GraphicsMechanics::WINDOW_HEIGHT - (y * yScale)) - yShiftSf;
    std::vector<double> point;
    point.push_back(newX);
    point.push_back(newY);
    return new Point(point);
}

Point *GraphicsMechanics::convertToCartesian(double minX, double maxX, double minY, double maxY, Point *p)
{
    
    double intervalX = maxX - minX;
    double xScale = WINDOW_WIDTH / intervalX;
    double intervalY = maxY - minY;
    double yScale = WINDOW_HEIGHT / intervalY;
    double xShiftCart = intervalX / 2;
    double xShiftSf = xShiftCart * xScale;
    double yShiftCart = intervalY / 2;
    double yShiftSf = yShiftCart * yScale;
    double x = p->getIthCoordinate(0);
    double y = p->getIthCoordinate(1);
    double newX = (x - xShiftSf) / xScale;
    double newY = -(y + yShiftSf - GraphicsMechanics::WINDOW_HEIGHT) / yScale;
    //    double newY = GraphicsMechanics::WINDOW_HEIGHT-(y*yScale)-yShiftSf;
    //convertY(F(midX)*Main.scale)-Main.yShift
    //convertY -> main.height-y
    std::vector<double> point;
    point.push_back(newX);
    point.push_back(newY);
    return new Point(point);
    
}

double GraphicsMechanics::getXScale(double minX, double maxX)
{
    double intervalX = maxX - minX;
    double xScale = WINDOW_WIDTH / intervalX;
    return xScale;
}
double GraphicsMechanics::getYScale(double minY, double maxY)
{
    double intervalY = maxY - minY;
    double yScale = WINDOW_HEIGHT / intervalY;
    return yScale;
}