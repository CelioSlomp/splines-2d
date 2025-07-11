#include "../include/circle.hpp"

Circle::Circle(double x, double y, double z, double r)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->r = r;
}

void Circle::newX(double x)
{
    this->x = x;
}

void Circle::newY(double y)
{
    this->y = y;
}

void Circle::newZ(double z)
{
    this->z = z;
}

void Circle::newR(double r)
{
    this->r = r;
}