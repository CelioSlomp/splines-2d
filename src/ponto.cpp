#include "../include/ponto.hpp"

Ponto::Ponto(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Ponto::newX(double x)
{
    this->x = x;
}

void Ponto::newY(double y)
{
    this->y = y;
}

void Ponto::newZ(double z)
{
    this->z = z;
}

Ponto Ponto::operator+(const Ponto &p)
{
    return Ponto(x + p.x, y + p.y, z + p.z);
}

Ponto Ponto::operator*(const Ponto &p)
{
    return Ponto(x * p.x, y * p.y, z * p.z);
}

Ponto Ponto::operator*(double num)
{
    return Ponto(num * x, num * y, num * z);
}
