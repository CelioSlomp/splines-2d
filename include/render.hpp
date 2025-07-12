#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <point.hpp>
#include <vector>

class Render
{
public:
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Surface *screen = NULL;
    Render(const char *title, int x, int y);
    void destroyScreen();
    void clearScreen();
    void display();
    SDL_Renderer *getRender();
    SDL_Window *getWindow();
    void drawPoint(Point *p, std::vector<int> color);
    void drawLine(Point *p1, Point *p2, std::vector<int> color);
    void drawCircle(Point *p1, double r, std::vector<int> color);
};