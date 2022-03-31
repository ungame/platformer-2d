#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include "Object.hpp"
#include "Time.hpp"

#define PLAYER_SPEED 8.0F
#define PLAYER_JUMP_FORCE -16.0F
#define PLAYER_JUMP_DELAY 0.5F

class Player: public Object
{
    public:
        SDL_FPoint Speed;
        SDL_FPoint Direction;
        bool OnGround;
        Time* lastJump;

    public:
        Player(int w, int h, float x, float y);

    public:
        void Update();
};

#endif