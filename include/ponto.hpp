#include <iostream>

class Ponto
{
public:
    double x, y, z;
    Ponto(double x, double y, double z);
    void newX(double x);
    void newY(double y);
    void newZ(double z);
    Ponto operator+(const Ponto &p);
    Ponto operator*(const Ponto &p);
    Ponto operator*(double num);
};