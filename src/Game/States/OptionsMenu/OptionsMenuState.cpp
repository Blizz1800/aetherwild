#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>

#include "OptionsMenuState.hpp"
#include "Game/StateManager.hpp"

namespace Game
{

OptionsMenuState::OptionsMenuState(SDL_Renderer* renderer)
    : GameState(renderer),
      m_font(nullptr, TTF_CloseFont),
      m_title(nullptr, SDL_DestroyTexture),
      m_loaded(false)
{}

OptionsMenuState::~OptionsMenuState() = default;

bool OptionsMenuState::load()
{
    m_font.reset(TTF_OpenFont("assets/fonts/m6x11plus.ttf", 24));
    if (!m_font)
    {
        SDL_Log("OptionsMenuState: Couldn't open font: %s\n", SDL_GetError());
        return false;
    }

    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended(m_font.get(), "Options Menu", 0, SDL_Color{ 255, 255, 255, 255 });
    if (!textSurface)
    {
        SDL_Log("OptionsMenuState: Couldn't render text: %s\n", SDL_GetError());
        return false;
    }

    m_title.reset(SDL_CreateTextureFromSurface(m_renderer, textSurface));
    SDL_DestroySurface(textSurface);
    if (!m_title)
    {
        SDL_Log("OptionsMenuState: Couldn't create texture from surface: %s\n", SDL_GetError());
        return false;
    }

    m_loaded = true;
    return true;
}

void OptionsMenuState::render()
{
    if (!m_loaded || !m_title)
        return;

    int w = 0, h = 0;
    SDL_GetRenderOutputSize(m_renderer, &w, &h);

    float tw = 0, th = 0;
    SDL_GetTextureSize(m_title.get(), &tw, &th);

    SDL_FRect dst;
    dst.w = tw;
    dst.h = th;
    dst.x = (w - tw) / 2.0f;

    SDL_RenderTexture(m_renderer, m_title.get(), nullptr, &dst);
}

void OptionsMenuState::handleInput(const InputEvent& event)
{
    // Ejemplo: salir del menú de opciones si se presiona ESC.
    if (event.type == InputType::KEY_PRESSED && event.key == SDLK_ESCAPE)
    {
        std::printf("Pressed ESC\n");
        sStateMgr->startNewState(GameStates::MAIN_MENU, m_renderer);
    }
}

}