#include "StateManager.hpp"
#include "States/MainMenu/MainMenuState.hpp"
#include "States/OptionsMenu/OptionsMenuState.hpp"

Game::StateManager::StateManager()
{
    targetState = nullptr;
}

Game::StateManager::~StateManager()
{
    if (targetState)
    {
        delete targetState;
        targetState = nullptr;
    }

    for (auto it : lastStates)
    {
        if (!it) continue;

        delete it;
        it = nullptr;
    }
}

Game::GameState* Game::StateManager::CreateNewState(GameStates state, SDL_Renderer* renderer, bool preload)
{
    Game::GameState* st = nullptr;
    switch (state)
    {
        case GameStates::MAIN_MENU:
            st = new MainMenuState(renderer);
            break;
        default:
            SDL_SetError("State not recognized!");
            break;
    }
    
    if (st && preload)
    {
        // TODO: Load the state assets in background
        if (!st->load())
        {
            delete st;
            st = nullptr;
            SDL_SetError("Failed to load state assets!");
        }
    }
    return st;
}

void Game::StateManager::EnterInState(Game::GameState *state)
{
    targetState = state;
    targetState->enter();
}

Game::GameState* Game::StateManager::startNewState(GameStates state, SDL_Renderer* renderer)
{
    CleanOldState();
    if (Game::GameState* newState = CreateNewState(state, renderer, true)) 
    {
        EnterInState(newState);
        return targetState;
    }
    return nullptr;
}

Game::GameState *Game::StateManager::getState(int index)
{
    if (index == -1)
        return targetState;
    else if (index >= 0 && index < static_cast<int>(lastStates.size()))
        return lastStates[index];
    return nullptr;
}

void Game::StateManager::CleanOldState()
{
    if (targetState)
    {
        targetState->exit();
        lastStates.push_back(targetState);
        targetState = nullptr;
    }
}