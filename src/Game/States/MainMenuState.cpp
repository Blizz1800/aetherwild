#include <ostream>
#include "MainMenuState.hpp"

Game::MainMenuState::~MainMenuState()
{
    if (m_title)
    {
        SDL_DestroyTexture(m_title);
        m_title = nullptr;
    }
    if (m_font)
    {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
}

void Game::MainMenuState::enter()
{
    sInputMgr->subscribe(this);
    if(!m_isLoaded)
        load();
}

void Game::MainMenuState::exit()
{
    sInputMgr->unsubscribe(this);
}

void Game::MainMenuState::update(const float &dt)
{
}

bool Game::MainMenuState::load()
{
    m_font = TTF_OpenFont("assets/fonts/m6x11plus.ttf", 24);
    if (!m_font)
    {
        SDL_Log("Couldn't open font: %s\n", SDL_GetError());
        return m_isLoaded;
    }
    TTF_SetFontSize(m_font, 128);
    SDL_Surface *text = TTF_RenderText_Blended(m_font, "Main Menu", 0, SDL_Color{255, 255, 255, 255});
    if (!text)
    {
        SDL_Log("Couldn't render text: %s\n", SDL_GetError());
        return m_isLoaded;
    }
    m_title = SDL_CreateTextureFromSurface(m_renderer, text);
    if (!m_title)
    {
        SDL_Log("Couldn't create texture from surface: %s\n", SDL_GetError());
        SDL_DestroySurface(text);
        return m_isLoaded;
    }
    SDL_DestroySurface(text);
    m_isLoaded = true;
    return m_isLoaded;
}

void Game::MainMenuState::render()
{
    int w = 0, h = 0;
    SDL_FRect dst;

    /* Center the text and scale it up */
    SDL_GetRenderOutputSize(m_renderer, &w, &h);
    SDL_GetTextureSize(m_title, &dst.w, &dst.h);

    SDL_RenderTexture(m_renderer, m_title, NULL, &dst);
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
            default: break;
        }
    }
}

void Game::MainMenuState::startNewGame()
{
    std::printf("Pressed: Enter\n");
}

void Game::MainMenuState::exitGame()
{
    std::printf("Pressed: ESC\n");
}

void Game::MainMenuState::moveMenuUp()
{
    std::printf("Pressed: UP\n");
}

void Game::MainMenuState::moveMenuDown()
{
    std::printf("Pressed: DOWN\n");
}
