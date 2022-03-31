#include "Object.hpp"
#include "Color.hpp"

#include <SDL2/SDL.h>

Object::Object()
{
    Width = 0;
    Height = 0;
    Position = { 0, 0 };
    Color = Color::Grey();
}

Object::Object(int w, int h, float x, float y, SDL_Color color)
{
    Width = w;
    Height = h;
    Position = { x, y };
    Color = color;
}

SDL_Rect Object::GetRect()
{
    int x = Position.x;
    int y = Position.y;
    
    SDL_Rect rect = { x, y, Width, Height };

    return rect;
}

void Object::DrawRect(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_Rect rect = GetRect();
    SDL_RenderFillRect(renderer, &rect);
}