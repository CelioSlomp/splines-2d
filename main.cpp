#include "include/ponto.hpp"
#include <vector>

using namespace std;

Ponto calcPontoMedio(Ponto p1, Ponto p2, double t)
{
    return (p1 * (1.0 - t)) + (p2 * t);
}

int main()
{
    double t;
    Ponto pA = Ponto(0, 0, 0);
    Ponto pB = Ponto(1, 1, 1);
    Ponto pC = Ponto(2, 2, 2);
    for (int i = 1; i <= 10; i++)
    {
        t = (double)i / 10.0;

        Ponto p1 = calcPontoMedio(pA, pB, t); // A to B
        Ponto p2 = calcPontoMedio(pB, pC, t); // B to C
        Ponto p3 = calcPontoMedio(p1, p2, t); // AB to BC

        cout << p3.x << endl;
        // cout << p1.x << endl;
        // cout << p2.x << endl;
        cout << "-" << endl;
    }

    return 0;
}