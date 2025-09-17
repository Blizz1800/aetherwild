#include "MainMenuState.hpp"

void MainMenuState::enter()
{
}

void MainMenuState::exit()
{
}

void MainMenuState::update(const float &dt)
{
}

void MainMenuState::render()
{
}

void MainMenuState::handleInput(const InputEvent &event)
{
    if (event.type == InputType::KEY_PRESSED)
    {
        switch (event.key)
        {
        case SDLK_RETURN: // Enter
            startNewGame();
            break;
        case SDLK_ESCAPE: // ESC
            exitGame();
            break;
        case SDLK_UP:
            moveMenuUp();
            break;
        case SDLK_DOWN:
            moveMenuDown();
            break;
        }
    }
}

void MainMenuState::startNewGame()
{
    // Código para inicializar el menú principal
}

void MainMenuState::exitGame()
{
    // Código para salir del juego
}

void MainMenuState::moveMenuUp()
{
    // Código para mover la selección del menú hacia arriba
}

void MainMenuState::moveMenuDown()
{
    // Código para mover la selección del menú hacia abajo
}
