#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

#include "Object.hpp"
#include "Player.hpp"

#define GRAVITY 0.8F

class Level
{
    private:
        std::vector<Object*> _tiles;
        Player* _player;
        bool _reset;
        int _height;
        int _worldShift;

    public:
        Level(const std::string levelMap[], const int levelHeight, const int tileSize);
        ~Level();

    public:
        void Run(SDL_Renderer* renderer);

    public:
        inline bool Reset() { return _reset; }

    private:
        void applyGravity();
        void handleHorizontalCollision();
        void handleVerticalCollision();
        void handleCamera();
};

#endif