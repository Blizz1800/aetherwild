#include "Game.hpp"

#include <string>
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Utils/Constants.hpp"

Game::GameClass::GameClass() : m_running(false)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    if (!TTF_Init())
    {
        SDL_Log("SDL_ttf could not initialize! SDL error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    if (!SDL_CreateWindowAndRenderer(
            Game::Constants::TITLE,
            Game::Constants::SCREEN_WIDTH,
            Game::Constants::SCREEN_HEIGHT,
            0x0, &m_window, &m_renderer))
    {
        SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
        SDL_Quit();
    };
}

Game::GameClass::~GameClass()
{
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
}

void Game::GameClass::run()
{
    m_running = true;

    // Set the frame rate
    const int frameDelay = 1000 / Game::Constants::FPS;

    sStateMgr->startNewState(MAIN_MENU, m_renderer);

    // The event data
    SDL_Event e;
    SDL_zero(e);

    while (m_running)
    {
        Uint32 frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e))
        {
            // If event is quit type
            if (e.type == SDL_EVENT_QUIT)
            {
                // End the main loop
                m_running = false;
                break;
            }
            // Create an input event from SDL event
            InputEvent event = InputEvent(InputType::KEY_PRESSED, e.key.key);
            sStateMgr->getState()->handleInput(event);
        }
        // Fill the surface white
        // SDL_FillSurfaceRect(m_screenSurface, nullptr, SDL_MapSurfaceRGB(m_screenSurface, 0x0, 0x0, 0x0));
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);

        // Handle state events
        // m_stateManager->getState()->update();
        sStateMgr->getState()->render();

        // Update the surface
        SDL_RenderPresent(m_renderer);

        // Control de framerate
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    close();
}

void Game::GameClass::close()
{
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;

    // Destroy window
    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}