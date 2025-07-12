#include "../include/spline.hpp"

Spline::Spline(std::vector<Point> &points, double r)
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
        h.push_back(points[i + 1].x - points[i].x);
}

Point Spline::cubicNatural(double t)
{
    if (!h.size())
        fillH();
}

std::vector<double> Spline::solveTridiagonal()
{
    // Using Thomas Method
    int n = b.size();
    std::vector<double> cprime(n, 0.0), dprime(n, 0.0), z(n, 0.0);

    cprime[0] = c[0] / b[0];
    dprime[0] = d[0] / b[0];

    double m;
    for (int i = 1; i < n; ++i)
    {
        m = b[i] - a[i] * cprime[i - 1];
        cprime[i] = c[i] / m;
        dprime[i] = (d[i] - a[i] * dprime[i - 1]) / m;
    }
    z[n - 1] = dprime[n - 1];
    for (int i = n - 2; i >= 0; --i)
    {
        z[i] = dprime[i] - cprime[i] * z[i + 1];
    }

    return z;
}

void Spline::createSystem()
{
    double hprev, hnext;
    int n = points.size();
    a.resize(n - 2);
    b.resize(n - 2);
    c.resize(n - 2);
    d.resize(n - 2);

    for (int i = 1; i < n - 1; ++i)
    {
        hprev = points[i].x - points[i - 1].x;
        hnext = points[i + 1].x - points[i].x;

        a[i - 1] = hprev;
        b[i - 1] = 2 * (hprev + hnext);
        c[i - 1] = hnext;
        d[i - 1] = 6.0 * (((double)(points[i + 1].y - points[i].y) / hnext) - ((double)(points[i].y - points[i - 1].y) / hnext));
    }
}