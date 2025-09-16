#include "Game.hpp"

GameClass::GameClass()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        SDL_Quit();
    }
    if (!SDL_CreateWindowAndRenderer(
            Game::Constants::TITLE,
            Game::Constants::SCREEN_WIDTH,
            Game::Constants::SCREEN_HEIGHT,
            0x0, &this->m_window, &this->m_renderer))
    {
        SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
        SDL_Quit();
    };
}

GameClass::~GameClass()
{
}

void GameClass::run()
{
    this->m_screenSurface = SDL_GetWindowSurface(this->m_window);
    this->m_running = true;

    // The event data
    SDL_Event e;
    SDL_zero(e);

    while (this->m_running)
    {
        while (SDL_PollEvent(&e))
        {
            // If event is quit type
            if (e.type == SDL_EVENT_QUIT)
            {
                // End the main loop
                m_running = false;
            }
            // Fill the surface white
            SDL_FillSurfaceRect(this->m_screenSurface, nullptr, SDL_MapSurfaceRGB(this->m_screenSurface, 0x0, 0x0, 0x0));

            // Render image on screen
            // SDL_BlitSurface(gHelloWorld, nullptr, this->m_screenSurface, nullptr);

            // Update the surface
            SDL_UpdateWindowSurface(this->m_window);
        }
    }

    this->close();
}

void GameClass::close()
{
    // Clean up surface
    SDL_DestroySurface(this->m_screenSurface);
    this->m_screenSurface = nullptr;

    // Destroy window
    SDL_DestroyWindow(this->m_window);
    this->m_window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}