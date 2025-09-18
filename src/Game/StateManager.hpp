#pragma once

#include "GameState.hpp"
#include "States/MainMenuState.hpp"
#include <vector>

namespace Game
{
    enum GameStates
    {
        MAIN_MENU,
    };

    class StateManager
    {
    private:
        GameState *targetState;
        SDL_Renderer *m_renderer;
        std::vector<GameState *> lastStates;

    public:
        StateManager(SDL_Renderer *m_renderer);
        ~StateManager();
        GameState *createNewState(GameStates state, bool preload = false);
        void enterState(GameState *state);
        GameState *startNewState(GameStates state);
        GameState *getState(int index = -1);
        GameState *getLastState();
        GameState *getFirstState();
    };
}