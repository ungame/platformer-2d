#ifndef COLOR_HPP
#define COLOR_HPP

#include <SDL2/SDL.h>

class Color
{
    private:
        SDL_Color _rgba;

    public:
        Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = SDL_ALPHA_TRANSPARENT) { _rgba = {r, g, b, a}; }
        inline SDL_Color RGBA() { return _rgba; }

    public:
        inline static SDL_Color Red() { return Color(255, 0, 0).RGBA(); }
        inline static SDL_Color Green() { return Color(0, 255, 0).RGBA(); }
        inline static SDL_Color Blue() { return Color(0, 0, 255).RGBA(); }
        inline static SDL_Color Black() { return Color(0, 0, 0).RGBA(); }
        inline static SDL_Color White() { return Color(255, 255, 255).RGBA(); }
        inline static SDL_Color Grey() { return Color(189, 189, 189).RGBA(); }
};

#endif