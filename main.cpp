#include "include/render.hpp"
#include <vector>

using namespace std;

int windowHeight = 600;
int windowWidth = 600;

int quit = 0;
SDL_Event e;

Render mainWindow = Render("Splines", windowWidth, windowHeight);
SDL_Renderer *sdl_render = mainWindow.getRender();

vector<int> blackColor = {0x00, 0x00, 0x00};
vector<int> whiteColor = {0xFF, 0xFF, 0xFF};

vector<Point> points;

Point calcPoint(Point p1, Point p2, double t)
{
    return (p1 * (1.0 - t)) + (p2 * t);
}

void loop()
{
    double t;
    Point pA = Point(0, 0, 0);
    mainWindow.drawCircle(&pA, 5, blackColor);
    Point pB = Point(100, 300, 0);
    mainWindow.drawCircle(&pB, 5, blackColor);
    Point pC = Point(200, 500, 0);
    mainWindow.drawCircle(&pC, 5, blackColor);
    Point pD = Point(300, 100, 0);
    mainWindow.drawCircle(&pD, 5, blackColor);
    points.push_back(pA);
    points.push_back(pB);
    points.push_back(pC);
    points.push_back(pD);

    Spline spl = Spline(points, 10.0);

    spl.createSystem();
    spl.solveTridiagonal();

    /*for (int i = 1; i <= 100; i++)
    {
        t = (double)i / 100.0;

        Point p1 = calcPoint(pA, pB, t); // A to B
        Point p2 = calcPoint(pB, pC, t); // B to C
        Point p3 = calcPoint(p1, p2, t); // AB to BC
        mainWindow.drawPoint(&p3, blackColor);
    }
    // mainWindow.drawLine(&pA, &pB, blackColor);
    // mainWindow.drawLine(&pB, &pC, blackColor);
    */
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