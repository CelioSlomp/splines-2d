#include "include/render.hpp"
#include <vector>

using namespace std;

int windowHeight = 600;
int windowWidth = 600;

int quit = 0;
SDL_Event e;

Render mainWindow = Render("Splines", windowWidth, windowHeight);
SDL_Renderer *sdl_render = mainWindow.getRender();

vector<int> corPreta = {0x00, 0x00, 0x00};
vector<int> corBranca = {0xFF, 0xFF, 0xFF};

Point calcPointMedio(Point p1, Point p2, double t)
{
    return (p1 * (1.0 - t)) + (p2 * t);
}

void loop()
{
    double t;
    Point pA = Point(0, 0, 0);
    Point pB = Point(100, 100, 0);
    Point pC = Point(500, 500, 0);
    for (int i = 1; i <= 10; i++)
    {
        t = (double)i / 10.0;

        Point p1 = calcPointMedio(pA, pB, t); // A to B
        Point p2 = calcPointMedio(pB, pC, t); // B to C
        Point p3 = calcPointMedio(p1, p2, t); // AB to BC
    }
    mainWindow.drawLine(&pA, &pB, corPreta);
    mainWindow.drawLine(&pB, &pC, corPreta);
}

int main()
{
    SDL_UpdateWindowSurface(mainWindow.getWindow());

    while (!quit)
    {
        mainWindow.clearScreen();
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }
        loop();
        mainWindow.display();
    }
    mainWindow.destroyScreen();

    return 0;
}