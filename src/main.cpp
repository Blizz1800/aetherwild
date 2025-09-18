#include <iostream>
#include "Game/Game.hpp"

using namespace Game;

int main()
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