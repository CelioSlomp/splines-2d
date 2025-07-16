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
    mainWindow.drawLine(&pA, &pB, blackColor);
    mainWindow.drawLine(&pB, &pC, blackColor);
    mainWindow.drawLine(&pC, &pD, blackColor);
    mainWindow.drawLine(&pD, &pE, blackColor);
    mainWindow.drawLine(&pE, &pF, blackColor);
    mainWindow.drawLine(&pF, &pG, blackColor);
    for (int i = 0; i < points.size(); i++)
        mainWindow.drawCircle(&points[i], 5, blackColor);
}

int main()
{
    SDL_UpdateWindowSurface(mainWindow.getWindow());

    pA = Point(50, 100, 60);
    pB = Point(100, 300, 100);
    pC = Point(150, 470, 200);
    pD = Point(200, 240, 150);
    pE = Point(250, 300, 250);
    pF = Point(300, 400, 350);
    pG = Point(350, 450, 450);

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