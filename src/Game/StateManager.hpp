#pragma once

#include "GameState.hpp"
#include "States/MainMenuState.hpp"
#include <vector>

namespace Game
{
    enum GameStates : uint8_t
    {
        MAIN_MENU,
    };

    class StateManager
    {
    private:
        StateManager();
        ~StateManager();

        GameState* targetState;
        std::vector<GameState *> lastStates;

        void CleanOldState();
        GameState* CreateNewState(GameStates state, SDL_Renderer* renderer, bool preload = false);

    public:
        StateManager(const StateManager&) = delete;
        StateManager& operator=(const StateManager&) = delete;
        StateManager(StateManager&&) = delete;
        StateManager& operator=(StateManager&&) = delete;

        static StateManager* getInstance()
        {
            static StateManager instance;
            return &instance;
        }

        void EnterInState(GameState *state);
        GameState* startNewState(GameStates state, SDL_Renderer* renderer);
        GameState* getState(int index = -1);
        GameState* getLastState();
        GameState* getFirstState();
    };
}

#define sStateMgr StateManager::getInstance()