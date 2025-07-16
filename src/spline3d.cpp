#include "../include/spline3d.hpp"
#include <cmath>

Spline3d::Spline3d(std::vector<Point> &points, double r)
{
    this->points = points;
    this->r = r;
    double dx, dy, dz;
    int n = points.size();
    t.resize(n);
    t[0] = 0.0;

    for (int i = 1; i < n; ++i)
    {
        dx = points[i].x - points[i - 1].x;
        dy = points[i].y - points[i - 1].y;
        dz = points[i].z - points[i - 1].z;
        t[i] = t[i - 1] + sqrt(dx * dx + dy * dy + dz * dz);
    }
    fillH();
}

void Spline3d::fillH()
{
    int n = points.size();
    for (int i = 0; i < n - 1; ++i)
        h.push_back(t[i + 1] - t[i]);
}

void Spline3d::solveTridiagonal()
{

    createSystem();
    solveTridiagonalDimension(zx);

    int n = points.size();
    double hprev, hnext;
    for (int i = 1; i < n - 1; ++i)
    {
        hprev = t[i] - t[i - 1];
        hnext = t[i + 1] - t[i];
        d[i - 1] = 6.0 * ((points[i + 1].y - points[i].y) / hnext - (points[i].y - points[i - 1].y) / hprev);
    }
    solveTridiagonalDimension(zy);

    for (int i = 1; i < n - 1; ++i)
    {
        hprev = t[i] - t[i - 1];
        hnext = t[i + 1] - t[i];
        d[i - 1] = 6.0 * ((points[i + 1].z - points[i].z) / hnext - (points[i].z - points[i - 1].z) / hprev);
    }
    solveTridiagonalDimension(zz);
}

void Spline3d::solveTridiagonalDimension(std::vector<double> &z)
{
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

    z.resize(points.size());
    z[0] = 0.0;
    z[points.size() - 1] = 0.0;
    for (int i = 1; i < points.size() - 1; ++i)
    {
        z[i] = zInternal[i - 1];
    }
}

void Spline3d::createSystem()
{

    int n = points.size();

    a.resize(n - 2);
    b.resize(n - 2);
    c.resize(n - 2);
    d.resize(n - 2);
    double hprev, hnext;
    for (int i = 1; i < n - 1; ++i)
    {
        hprev = t[i] - t[i - 1];
        hnext = t[i + 1] - t[i];
        a[i - 1] = (i == 1) ? 0 : hprev; // bem melhor usar essa forma
        b[i - 1] = 2 * (hprev + hnext);
        c[i - 1] = (i == n - 2) ? 0 : hnext;

        d[i - 1] = 6.0 * ((points[i + 1].x - points[i].x) / hnext - (points[i].x - points[i - 1].x) / hprev);
    }
}

Point Spline3d::evaluateSpline(double tp)
{
    int i = 0;
    double x, y, z;
    while (i < t.size() - 1 && tp > t[i + 1])
    {
        i++;
    }
    x = evaluateDimension(tp, i, zx, 0);
    y = evaluateDimension(tp, i, zy, 1);
    z = evaluateDimension(tp, i, zz, 2);
    return Point(x, y, z);
}

double Spline3d::evaluateDimension(double tp, int i, std::vector<double> &zdim, int var)
{
    // var values:
    // 0 -> x; 1 -> y; 2 -> z
    double pi, pi1;
    if (var == 0)
    {
        pi = points[i].x;
        pi1 = points[i + 1].x;
    }
    if (var == 1)
    {
        pi = points[i].y;
        pi1 = points[i + 1].y;
    }
    if (var == 2)
    {
        pi = points[i].z;
        pi1 = points[i + 1].z;
    }
    double A = (t[i + 1] - tp) / h[i];
    double B = (tp - t[i]) / h[i];

    double term1 = (zdim[i] / 6.0) * pow(t[i + 1] - tp, 3) / h[i];
    double term2 = (zdim[i + 1] / 6.0) * pow(tp - t[i], 3) / h[i];
    double term3 = (pi - zdim[i] * h[i] * h[i] / 6.0) * A;
    double term4 = (pi1 - zdim[i + 1] * h[i] * h[i] / 6.0) * B;

    return term1 + term2 + term3 + term4;
}