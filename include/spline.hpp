#include <iostream>
#include <vector>
#include <point.hpp>

class Spline
{
public:
    double r;
    std::vector<Point> points;
    std::vector<Point> cPoints;
    std::vector<double> h, a, b, c, d, z;
    Spline(std::vector<Point> &points, double r);
    Point bezierPoint(Point p1, Point p2, Point p3, Point p4, double t);
    Point catmullRom(Point p1, Point p2, Point p3, Point p4, double t);
    void fillH();
    void solveTridiagonal();
    void createSystem();
    double evaluateSpline(double t, int i);
};