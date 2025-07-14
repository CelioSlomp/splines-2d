#include <iostream>

class Point
{
public:
    double x, y, z;
    int controle;
    Point();
    Point(double x, double y, double z);
    Point(double x, double y, double z, int controle);
    void newX(double x);
    void newY(double y);
    void newZ(double z);
    Point operator+(const Point &p);
    Point operator*(const Point &p);
    Point operator*(double num);
};