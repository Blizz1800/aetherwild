#include "StateManager.hpp"

StateManager::StateManager(SDL_Renderer *m_renderer)
    : m_renderer(m_renderer)
{
    this->targetState = nullptr;
}

StateManager::~StateManager()
{
    if (this->targetState)
    {
        delete this->targetState;
        this->targetState = nullptr;
    }
}

GameState *StateManager::createNewState(GameStates state, bool preload)
{
    GameState *st = nullptr;
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

void StateManager::enterState(GameState *state)
{
    this->targetState = state;
    this->targetState->enter();
}

GameState *StateManager::startNewState(GameStates state)
{
    if (this->targetState)
    {
        this->targetState->exit();
        this->lastStates.push_back(this->targetState);
        this->targetState = nullptr;
    }
    GameState *newState = this->createNewState(state, true);
    if (!newState)
        return nullptr;
    this->enterState(newState);
    return this->targetState;
}

GameState *StateManager::getState(int index)
{
    if (index == -1)
        return this->targetState;
    else if (index >= 0 && index < (int)this->lastStates.size())
        return this->lastStates[index];
    return nullptr;
}