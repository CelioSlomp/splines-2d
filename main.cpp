#include "include/point.hpp"
#include <vector>

using namespace std;

Point calcPointMedio(Point p1, Point p2, double t)
{
    return (p1 * (1.0 - t)) + (p2 * t);
}

int main()
{
    double t;
    Point pA = Point(0, 0, 0);
    Point pB = Point(1, 1, 1);
    Point pC = Point(2, 2, 2);
    for (int i = 1; i <= 10; i++)
    {
        t = (double)i / 10.0;

        Point p1 = calcPointMedio(pA, pB, t); // A to B
        Point p2 = calcPointMedio(pB, pC, t); // B to C
        Point p3 = calcPointMedio(p1, p2, t); // AB to BC

        cout << p3.x << endl;
        // cout << p1.x << endl;
        // cout << p2.x << endl;
        cout << "-" << endl;
    }

    return 0;
}