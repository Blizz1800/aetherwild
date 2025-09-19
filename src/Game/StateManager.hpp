#pragma once

#include <vector>
#include "GameState.hpp"

namespace Game
{
    enum GameStates : uint8_t
    {
        MAIN_MENU       = 1,
        OPTIONS_MENU,
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
        void EnterInState(GameState *state);

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

        GameState* startNewState(GameStates state, SDL_Renderer* renderer);
        GameState* getState(int index = -1);
        GameState* getLastState();
        GameState* getFirstState();
    };
}

#define sStateMgr StateManager::getInstance()