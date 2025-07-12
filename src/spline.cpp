#include "../include/spline.hpp"

Spline::Spline(std::vector<Point> points, std::vector<Point> cPoints, double r)
{
    this->points = points;
    this->cPoints = cPoints;
    this->r = r;
}

Point Spline::bezierPoint(Point p1, Point p2, Point p3, Point p4, double t)
{
    // (1-t)
    double omt = 1 - t;
    return p1 * omt * omt * omt + p2 * omt * omt * 3 * t + p3 * omt * t * t + p4 * t * t * t;
}

Point Spline::catmullRom(Point p1, Point p2, Point p3, Point p4, double t)
{
}

void Spline::fillH()
{
    int n = points.size();
    for (int i = 0; i < n - 1; ++i)
        h.push_back(points.at(i).x - points.at(i).x);
}

Point Spline::cubicNatural(double t)
{
    if (!h.size())
        fillH();
    else
}