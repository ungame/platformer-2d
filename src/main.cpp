#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "Time.hpp"
#include "Settings.hpp"
#include "Object.hpp"
#include "Input.hpp"
#include "Color.hpp"
#include "Level.hpp"

void setWindowTitle(SDL_Window* window, int frameTime);

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to init: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create window: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create renderer: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Color bgColor = Color::Black();

    Level* level = new Level(LEVEL_MAP, LEVEL_HEIGHT, TILE_SIZE);

    int frameTime = 0;
    Uint32 previousTime = SDL_GetTicks();
    const int fps = 1000 / 60;

    bool running = true;

    while(running)
    {
        running = Input::Instance()->Listen();

        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderClear(renderer);

        setWindowTitle(window, frameTime);

        if(level->Reset())
        {
            delete level;
            level = new Level(LEVEL_MAP, LEVEL_HEIGHT, TILE_SIZE); 
        }

        level->Run(renderer);

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - previousTime;
        previousTime = SDL_GetTicks();

        if(fps > frameTime)
            SDL_Delay(fps - frameTime);   
    }

    delete level;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

void setWindowTitle(SDL_Window* window, int frameTime)
{
    std::string title = "";
    Time* time = new Time();

    title = std::string(WINDOW_TITLE);
    title += " | ";

    title += std::string(time->String());
    title += " | ";
    delete time;

    SDL_Point cursor = Input::Instance()->GetCursor();
    title += "MX=" + std::to_string(cursor.x);
    title += " | ";

    title += "MY=" + std::to_string(cursor.y);
    title += " | ";

    title += "FrameTime=" + std::to_string(frameTime);

    SDL_SetWindowTitle(window, title.c_str());
}