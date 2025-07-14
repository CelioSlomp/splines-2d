#include "include/render.hpp"

using namespace std;

int windowHeight = 500;
int windowWidth = 500;

int quit = 0;
SDL_Event e;

Render mainWindow = Render("Splines", windowWidth, windowHeight);
SDL_Renderer *sdl_render = mainWindow.getRender();

vector<int> blackColor = {0x00, 0x00, 0x00};
vector<int> whiteColor = {0xFF, 0xFF, 0xFF};

vector<Point> points;
Point pA, pB, pC, pD, pE, pF, pG, pH, pI, pJ;

Point calcPoint(Point p1, Point p2, double t)
{
    return (p1 * (1.0 - t)) + (p2 * t);
}

void loop()
{
    double t;
    Spline spl = Spline(points, 10.0);

    for (int i = 0; i < points.size(); i++)
    {
        mainWindow.drawCircle(&points[i], 5, blackColor);
    }

    spl.createSystem();
    spl.solveTridiagonal();

    int n = points.size();
    Point pN;
    for (int i = 0; i < n - 1; i++)
    {
        for (double t = points[i].x; t <= points[i + 1].x; t += 0.1)
        {
            double y = spl.evaluateSpline(t, i);
            pN = Point(t, y, 0);
            mainWindow.drawPoint(&pN, blackColor);
        }
    }

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

    pA = Point(50, 100, 0);
    pB = Point(100, 300, 0);
    pC = Point(150, 470, 0);
    pD = Point(200, 240, 0);
    pE = Point(250, 300, 0);
    pF = Point(300, 400, 0);
    pG = Point(350, 450, 0);

    points.push_back(pA);
    points.push_back(pB);
    points.push_back(pC);
    points.push_back(pD);
    points.push_back(pE);
    points.push_back(pF);
    points.push_back(pG);

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