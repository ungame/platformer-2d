#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>

#include "Color.hpp"

class Object
{
    public:
        int Width;
        int Height;
        SDL_FPoint Position;
        SDL_Color Color;

    public:
        Object();
        Object(int w, int h, float x, float y, SDL_Color color = Color::Grey());
        SDL_Rect GetRect();

    public:
        void DrawRect(SDL_Renderer* renderer);
};

#endif