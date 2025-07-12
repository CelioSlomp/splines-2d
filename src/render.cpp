#include "../include/render.hpp"

Render::Render(const char *titulo, int t_x, int t_y)
{

    window = SDL_CreateWindow(titulo, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              t_x, t_y, SDL_WINDOW_SHOWN);
    if (window == NULL)
        printf("Error: ", SDL_GetError());
    else
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (render == NULL)
        printf("Error: ", SDL_GetError());
    else
    {
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
        screen = SDL_GetWindowSurface(window);
    }
}

void Render::destroyScreen()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
}

void Render::clearScreen()
{
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(render);
}

void Render::display()
{
    SDL_RenderPresent(render);
}

SDL_Renderer *Render::getRender()
{
    return render;
}

SDL_Window *Render::getWindow()
{
    return window;
}

void Render::drawPoint(Point *p, std::vector<int> color)
{
    SDL_SetRenderDrawColor(render, color.at(0), color.at(1), color.at(2), 0xFF);
    SDL_RenderDrawPoint(render, p->x, p->y);
}

void Render::drawLine(Point *p1, Point *p2, std::vector<int> color)
{
    SDL_SetRenderDrawColor(render, color.at(0), color.at(1), color.at(2), 0xFF);
    SDL_RenderDrawLine(render, p1->x, p1->y, p2->x, p2->y);
}

void Render::drawCircle(Point *p, double r, std::vector<int> color)
{
    double fat = 180;
    for (int i = 0; i < fat; i++)
    {
        SDL_SetRenderDrawColor(render, color.at(0), color.at(1), color.at(2), 0xFF);
        SDL_RenderDrawPoint(render, r * cos(((double)i / fat) * 2 * M_PI) + p->x,
                            r * sin(((double)i / fat) * 2 * M_PI) + p->y);
    } // for i<fat
}