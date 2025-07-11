#include <iostream>
#include <vector>
#include <point.hpp>
#include <circle.hpp>

class Spline
{
    Spline(std::vector<Point> points, std::vector<Point> cPoints, double r);
    std::vector<Point> points;
    std::vector<Point> cPoints;
};