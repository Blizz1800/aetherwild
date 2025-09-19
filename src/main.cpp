#include <iostream>
#include <SDL3/SDL_main.h>
#include "Game/Game.hpp"

using namespace Game;

int main(int argc, char* argv[])
{
    try
    {
        GameClass game;
        game.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}