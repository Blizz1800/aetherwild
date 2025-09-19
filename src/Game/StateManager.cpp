#include "StateManager.hpp"

Game::StateManager::StateManager(SDL_Renderer *m_renderer)
    : m_renderer(m_renderer)
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
}

Game::GameState *Game::StateManager::createNewState(GameStates state, bool preload)
{
    Game::GameState *st = nullptr;
    switch (state)
    {
    case GameStates::MAIN_MENU:
        st = new MainMenuState(m_renderer);
        break;
    default:
        SDL_SetError("State not recognized!");
        break;
    }
    if (st && preload)
    {
        // TODO: Load the state assets in background
        if (!st->load())
            SDL_SetError("Failed to load state assets!");
    }
    return st;
}

void Game::StateManager::enterState(Game::GameState *state)
{
    targetState = state;
    targetState->enter();
}

Game::GameState *Game::StateManager::startNewState(GameStates state)
{
    if (targetState)
    {
        targetState->exit();
        lastStates.push_back(targetState);
        targetState = nullptr;
    }
    Game::GameState *newState = createNewState(state, true);
    if (!newState)
        return nullptr;
    enterState(newState);
    return targetState;
}

Game::GameState *Game::StateManager::getState(int index)
{
    if (index == -1)
        return targetState;
    else if (index >= 0 && index < (int)lastStates.size())
        return lastStates[index];
    return nullptr;
}