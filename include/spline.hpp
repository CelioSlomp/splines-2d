#include <iostream>
#include <vector>
#include <point.hpp>

class Spline
{
    double r;
    std::vector<Point> points;
    std::vector<Point> cPoints;
    std::vector<double> h;
    Spline(std::vector<Point> points, std::vector<Point> cPoints, double r);
    Point bezierPoint(Point p1, Point p2, Point p3, Point p4, double t);
    Point catmullRom(Point p1, Point p2, Point p3, Point p4, double t);
    Point cubicNatural(double t);
    void fillH();
};