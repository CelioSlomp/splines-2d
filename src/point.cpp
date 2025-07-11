#include "../include/point.hpp"

Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->controle = 0;
}
Point::Point(double x, double y, double z, int controle)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->controle = controle;
}

void Point::newX(double x)
{
    this->x = x;
}

void Point::newY(double y)
{
    this->y = y;
}

void Point::newZ(double z)
{
    this->z = z;
}

Point Point::operator+(const Point &p)
{
    return Point(x + p.x, y + p.y, z + p.z);
}

Point Point::operator*(const Point &p)
{
    return Point(x * p.x, y * p.y, z * p.z);
}

Point Point::operator*(double num)
{
    return Point(num * x, num * y, num * z);
}
