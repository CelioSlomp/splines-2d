#include "include/ponto.hpp"

using namespace std;

int main()
{
    double t;
    Ponto p1 = Ponto(0, 0, 0);
    Ponto p2 = Ponto(1, 1, 0);
    for (int i = 1; i <= 10; i++)
    {
        t = (double)i / 10.0;

        Ponto pMedio = (p1 * (1.0 - t)) + (p2 * t);
        cout << pMedio.x << endl;
        // cout << p1.x << endl;
        // cout << p2.x << endl;
        cout << "-" << endl;
    }

    return 0;
}