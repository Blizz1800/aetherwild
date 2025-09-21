#pragma once

#include <string>
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Utils/Constants.hpp"

#include "Input/InputManager.hpp"
#include "StateManager.hpp"

namespace Game
{
    class GameClass
    {
    public:
        GameClass();
        ~GameClass();

        void run();
        void init();
        void cleanup();
        void close();

    private:
        void handleEvents();
        void update(float deltaTime);
        void render();

        SDL_Window *m_window;
        bool m_running;

        float deltaTime;

        SDL_Renderer *m_renderer;
        InputManager *m_inputManager;
    };
}