#include "MainMenuState.hpp"

void Game::MainMenuState::enter()
{
}

void Game::MainMenuState::exit()
{
}

void Game::MainMenuState::update(const float &dt)
{
}

bool Game::MainMenuState::load()
{
    this->font = TTF_OpenFont("assets/fonts/m6x11plus.ttf", 24);
    if (!font)
    {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return false;
    }
    TTF_SetFontSize(this->font, 128);
    SDL_Surface *text = TTF_RenderText_Blended(this->font, "Main Menu", 0, SDL_Color{255, 255, 255, 255});
    if (!text)
    {
        SDL_Log("Couldn't render text: %s\n", SDL_GetError());
        return false;
    }
    this->title = SDL_CreateTextureFromSurface(this->m_renderer, text);
    if (!this->title)
    {
        SDL_Log("Couldn't create texture from surface: %s\n", SDL_GetError());
        SDL_DestroySurface(text);
        return false;
    }
    SDL_DestroySurface(text);
    return true;
}

void Game::MainMenuState::render()
{
    int w = 0, h = 0;
    SDL_FRect dst;

    /* Center the text and scale it up */
    SDL_GetRenderOutputSize(this->m_renderer, &w, &h);
    SDL_GetTextureSize(this->title, &dst.w, &dst.h);

    SDL_RenderTexture(this->m_renderer, this->title, NULL, &dst);
}

void Game::MainMenuState::handleInput(const InputEvent &event)
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

void Game::MainMenuState::startNewGame()
{
    // Código para inicializar el menú principal
}

void Game::MainMenuState::exitGame()
{
    // Código para salir del juego
}

void Game::MainMenuState::moveMenuUp()
{
    // Código para mover la selección del menú hacia arriba
}

void Game::MainMenuState::moveMenuDown()
{
    // Código para mover la selección del menú hacia abajo
}
