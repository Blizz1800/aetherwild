#include "StateManager.hpp"

Game::StateManager::StateManager(SDL_Renderer *m_renderer)
    : m_renderer(m_renderer)
{
    this->targetState = nullptr;
}

Game::StateManager::~StateManager()
{
    if (this->targetState)
    {
        delete this->targetState;
        this->targetState = nullptr;
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
    this->targetState = state;
    this->targetState->enter();
}

Game::GameState *Game::StateManager::startNewState(GameStates state)
{
    if (this->targetState)
    {
        this->targetState->exit();
        this->lastStates.push_back(this->targetState);
        this->targetState = nullptr;
    }
    Game::GameState *newState = this->createNewState(state, true);
    if (!newState)
        return nullptr;
    this->enterState(newState);
    return this->targetState;
}

Game::GameState *Game::StateManager::getState(int index)
{
    if (index == -1)
        return this->targetState;
    else if (index >= 0 && index < (int)this->lastStates.size())
        return this->lastStates[index];
    return nullptr;
}