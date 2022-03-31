#include "Player.hpp"

#include <SDL2/SDL.h>

#include "Input.hpp"
#include "Time.hpp"

Player::Player(int w, int h, float x, float y): Object(w, h, x, y)
{
    Speed = { PLAYER_SPEED, 0 };
    Direction = { 0, 0 };
    OnGround = false;
    lastJump = new Time();
}

void Player::Update()
{
    Direction.x = 0;

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_RIGHT))
        Direction.x = 1;

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_LEFT))
        Direction.x = -1;

    if(Input::Instance()->KeyPressed(SDL_SCANCODE_SPACE))
    {
        if(OnGround && Time::Since(lastJump) >= PLAYER_JUMP_DELAY)
        {
            Direction.y = PLAYER_JUMP_FORCE;
            lastJump = new Time();
        }
    }
        
}