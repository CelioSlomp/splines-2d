#include <iostream>
#include <vector>
#include <point.hpp>

class Spline3d
{
public:
    double r;
    std::vector<Point> points;
    std::vector<Point> cPoints;
    std::vector<double> h, a, b, c, d, zx, zy, zz, t;
    Spline3d(std::vector<Point> &points, double r);
    void fillH();
    void solveTridiagonal();
    void solveTridiagonalDimension(std::vector<double> &z);
    void createSystem();
    Point evaluateSpline(double t);
    double evaluateDimension(double tp, int i, std::vector<double> &zdim, int var);
};