#include "../include/spline.hpp"
#include <cmath>

Spline::Spline(std::vector<Point> &points, double r)
{
    this->points = points;
    this->cPoints = cPoints;
    this->r = r;
    std::vector<double> z;
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

void Spline::solveTridiagonal()
{
    if (!h.size())
        fillH();
    // Using Thomas Method
    int n = b.size();
    std::vector<double> cprime(n, 0.0), dprime(n, 0.0), zInternal(n, 0.0);

    cprime[0] = c[0] / b[0];
    dprime[0] = d[0] / b[0];

    double m;
    for (int i = 1; i < n; ++i)
    {
        m = b[i] - a[i] * cprime[i - 1];
        cprime[i] = c[i] / m;
        dprime[i] = (d[i] - a[i] * dprime[i - 1]) / m;
    }

    zInternal[n - 1] = dprime[n - 1];
    for (int i = n - 2; i >= 0; --i)
    {
        zInternal[i] = dprime[i] - cprime[i] * zInternal[i + 1];
    }

    for (int i = 1; i < n + 1; ++i)
    {
        z[i] = zInternal[i - 1];
    }
}

void Spline::createSystem()
{
    int n = points.size();

    a.resize(n - 2);
    b.resize(n - 2);
    c.resize(n - 2);
    d.resize(n - 2);
    double hprev, hnext;
    for (int i = 1; i < n - 1; ++i)
    {
        hprev = points[i].x - points[i - 1].x;
        hnext = points[i + 1].x - points[i].x;

        a[i - 1] = (i == 1) ? 0 : hprev; // bem melhor usar essa forma
        b[i - 1] = 2 * (hprev + hnext);
        c[i - 1] = (i == n - 2) ? 0 : hnext;
        d[i - 1] = 6.0 * ((points[i + 1].y - points[i].y) / hnext - (points[i].y - points[i - 1].y) / hprev);
    }

    z.resize(n);
    z[0] = 0.0;
    z[n - 1] = 0.0;
}

double Spline::evaluateSpline(double t, int i)
{
    double A = (points[i + 1].x - t) / h[i];
    double B = (t - points[i].x) / h[i];

    double term1 = (z[i] / 6.0) * pow(points[i + 1].x - t, 3) / h[i];
    double term2 = (z[i + 1] / 6.0) * pow(t - points[i].x, 3) / h[i];
    double term3 = (points[i].y - z[i] * h[i] * h[i] / 6.0) * A;
    double term4 = (points[i + 1].y - z[i + 1] * h[i] * h[i] / 6.0) * B;

    return term1 + term2 + term3 + term4;
}