#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <memory>

#include "StateManager.hpp"
#include "Utils/Constants.hpp"

class GameClass
{
public:
    GameClass();
    ~GameClass();

    void run();
    void init();
    void cleanup();
    void close();

    static const int FPS = 60;

private:
    void handleEvents();
    void update(float deltaTime);
    void render();

    SDL_Window *m_window;
    bool m_running;

    SDL_Renderer *m_renderer;
    // std::unique_ptr<InputManager> m_inputManager;
    StateManager *m_stateManager;
};