#include "Game.hpp"

Game::GameClass::GameClass()
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
            0x0, &this->m_window, &this->m_renderer))
    {
        SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
        SDL_Quit();
    };
}

Game::GameClass::~GameClass()
{
    SDL_DestroyRenderer(this->m_renderer);
    this->m_renderer = nullptr;
    SDL_DestroyWindow(this->m_window);
    this->m_window = nullptr;
}

void Game::GameClass::run()
{
    this->m_stateManager = new StateManager(this->m_renderer);
    this->m_running = true;

    // Set the frame rate
    const int frameDelay = 1000 / Game::Constants::FPS;

    this->m_stateManager->startNewState(MAIN_MENU);

    // The event data
    SDL_Event e;
    SDL_zero(e);

    while (this->m_running)
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
            this->m_stateManager->getState()->handleInput(event);
        }
        // Fill the surface white
        // SDL_FillSurfaceRect(this->m_screenSurface, nullptr, SDL_MapSurfaceRGB(this->m_screenSurface, 0x0, 0x0, 0x0));
        SDL_SetRenderDrawColor(this->m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->m_renderer);

        // Handle state events
        // this->m_stateManager->getState()->update();
        this->m_stateManager->getState()->render();

        // Update the surface
        SDL_RenderPresent(this->m_renderer);

        // Control de framerate
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    this->close();
}

void Game::GameClass::close()
{
    SDL_DestroyRenderer(this->m_renderer);
    this->m_renderer = nullptr;

    // Destroy window
    SDL_DestroyWindow(this->m_window);
    this->m_window = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}