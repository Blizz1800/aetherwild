#include <ostream>
#include "MainMenuState.hpp"
#include "Game/StateManager.hpp"

namespace Game
{
MainMenuState::MainMenuState(SDL_Renderer* renderer)
    : GameState(renderer),
      m_font(nullptr, TTF_CloseFont),
      m_title(nullptr, SDL_DestroyTexture)
{}

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
    m_font.reset(TTF_OpenFont("assets/fonts/m6x11plus.ttf", 24));
    if (!m_font)
    {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return false;
    }
    TTF_SetFontSize(m_font.get(), 128);
    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> text = { TTF_RenderText_Blended(m_font.get(), "Main Menu", 0, SDL_Color{255, 255, 255, 255}), SDL_DestroySurface };
    if (!text)
    {
        SDL_Log("Couldn't render text: %s\n", SDL_GetError());
        return false;
    }
    m_title.reset(SDL_CreateTextureFromSurface(m_renderer, text.get()));
    if (!m_title)
    {
        SDL_Log("Couldn't create texture from surface: %s\n", SDL_GetError());
        SDL_DestroySurface(text.get());
        return false;
    }
    SDL_DestroySurface(text.get());
    return true;
}

void MainMenuState::render()
{
    int w = 0, h = 0;
    SDL_FRect dst;

    /* Center the text and scale it up */
    SDL_GetRenderOutputSize(m_renderer, &w, &h);
    SDL_GetTextureSize(m_title.get(), &dst.w, &dst.h);

    SDL_RenderTexture(m_renderer, m_title.get(), NULL, &dst);
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
            default: break;
        }
    }
}

void MainMenuState::startNewGame()
{
    std::printf("Pressed: Enter\n");
    sStateMgr->startNewState(GameStates::OPTIONS_MENU, m_renderer);
}

void MainMenuState::exitGame()
{
    std::printf("Pressed: ESC\n");
}

void MainMenuState::moveMenuUp()
{
    std::printf("Pressed: UP\n");
}

void MainMenuState::moveMenuDown()
{
    std::printf("Pressed: DOWN\n");
}
} // namespace Game

