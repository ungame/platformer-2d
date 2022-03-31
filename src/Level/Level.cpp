#include "Level.hpp"

#include <string>
#include <vector>

#include "Object.hpp"
#include "Color.hpp"

Level::Level(const std::string levelMap[], const int levelHeight, const int tileSize)
{
    _reset = false;
    _height = levelHeight * tileSize;
    _worldShift = 0;

    for(int row = 0; row < levelHeight; row++)
    {
        int cols = levelMap[row].length();

        for(int col = 0; col < cols; col++)
        {
            char cell = levelMap[row][col];

            if(cell == 'T')
            {
                float x = col * tileSize;
                float y = row * tileSize;
                Object* tile = new Object(tileSize, tileSize, x, y);
                _tiles.push_back(tile);
            }

            if(cell == 'P')
            {
                int playerWidth = tileSize / 2;
                float x = col * playerWidth;
                float y = row * playerWidth;
                _player = new Player(playerWidth, playerWidth, x, y);
                _player->Color = Color::Red();
            }
        }
    }
}

void Level::Run(SDL_Renderer* renderer)
{
    _player->Update();
    
    handleHorizontalCollision();
    handleVerticalCollision();
    handleCamera();

    for(Object* tile: _tiles)
    {
        tile->Position.x += _worldShift;
        tile->DrawRect(renderer);
    }

    _player->DrawRect(renderer);
}

void Level::applyGravity()
{
    _player->Direction.y += GRAVITY;
    _player->Position.y += _player->Direction.y;
}

void Level::handleHorizontalCollision()
{
    _player->Position.x += _player->Speed.x * _player->Direction.x;

    SDL_Rect playerRect = _player->GetRect();

    for(Object* tile: _tiles)
    {
        SDL_Rect tileRect = tile->GetRect();

        if(SDL_HasIntersection(&playerRect, &tileRect))
        {
            if(_player->Direction.x > 0)
                _player->Position.x = tileRect.x - _player->Width;
            else if(_player->Direction.x < 0)
                _player->Position.x = tileRect.x + tileRect.w;

            _player->Direction.x = 0;
        }
    }   
}

void Level::handleVerticalCollision()
{
    applyGravity();

    SDL_Rect playerRect = _player->GetRect();

    for(Object* tile: _tiles)
    {
        SDL_Rect tileRect = tile->GetRect();

        if(SDL_HasIntersection(&playerRect, &tileRect))
        {
            if(_player->Direction.y > 0)
            {
                _player->Position.y = tileRect.y - _player->Height;
                _player->OnGround = true;
                _player->Direction.y = 0;
            }
            else if(_player->Direction.y < 0)
            {
                _player->Position.y = tileRect.y + tileRect.h;
                _player->Direction.y = 0;
            }
        }
    }

    if((_player->OnGround && _player->Direction.y < 0) || _player->Direction.y > 1)
        _player->OnGround = false;

    if(playerRect.y > _height)
        _reset = true;
}

void Level::handleCamera()
{
    if(_player->Position.x < 200 && _player->Direction.x < 0)
    {
        _player->Speed.x = 0;
        _worldShift = PLAYER_SPEED;
    }
    else if(_player->Position.x > 1000 && _player->Direction.x > 0)
    {
        _player->Speed.x = 0;
        _worldShift = -PLAYER_SPEED;
    }
    else
    {
        _player->Speed.x = PLAYER_SPEED;
        _worldShift = 0; 
    }
}

Level::~Level()
{
    for(Object* tile: _tiles)
        delete tile;

    _tiles.clear();
    delete _player;
}