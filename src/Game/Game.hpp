#pragma once

#include "StateManager.hpp"

struct SDL_Window;
struct SDL_Renderer;

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
        // std::unique_ptr<InputManager> m_inputManager;
    };
}