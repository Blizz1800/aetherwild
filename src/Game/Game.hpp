#ifndef _GAME_HPP
#define _GAME_HPP

#include <SDL2/SDL.h>
#include <memory>

// class Renderer;
// class InputManager;
// class StateManager;

class Game {
public:
    Game();
    ~Game();
    
    static void run();
    void init();
    void cleanup();
    
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;
    static const int FPS = 60;

private:
    void handleEvents();
    void update(float deltaTime);
    void render();
    
    SDL_Window* m_window;
    bool m_running;
    
    // std::unique_ptr<Renderer> m_renderer;
    // std::unique_ptr<InputManager> m_inputManager;
    // std::unique_ptr<StateManager> m_stateManager;
};

#endif