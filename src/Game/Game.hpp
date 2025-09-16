#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <string>
#include <memory>

#include "Utils/Constants.hpp"

class GameClass {
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
    
    SDL_Window* m_window;
    SDL_Surface* m_screenSurface;
    bool m_running;
    
    SDL_Renderer* m_renderer;
    // std::unique_ptr<InputManager> m_inputManager;
    // std::unique_ptr<StateManager> m_stateManager;
};