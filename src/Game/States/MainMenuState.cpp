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

bool MainMenuState::load()
{
    this->font = TTF_OpenFont("assets/fonts/m3x6.ttf", 24);
    if (!font)
    {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return false;
    }
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

void MainMenuState::render()
{
    int w = 0, h = 0;
    SDL_FRect dst;
    const float scale = 4.0f;

    /* Center the text and scale it up */
    SDL_GetRenderOutputSize(this->m_renderer, &w, &h);
    SDL_SetRenderScale(this->m_renderer, scale, scale);
    SDL_GetTextureSize(this->title, &dst.w, &dst.h);
    // SDL_Log("After: %s", SDL_GetError());
    dst.x = ((w / scale) - dst.w) / 2;
    dst.y = ((h / scale) - dst.h) / 2;

    // SDL_Render
    SDL_RenderTexture(this->m_renderer, this->title, NULL, &dst);
    SDL_RenderPresent(this->m_renderer);
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
