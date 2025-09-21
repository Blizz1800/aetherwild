#include "InputManager.hpp"

Game::InputManager::~InputManager()
{
    if (event)
    {
        delete event;
        event = nullptr;
    }
    for (auto it : subscriptions)
    {
        if (!it)
            continue;
        delete it;
        it = nullptr;
    }
}

void Game::InputManager::subscribe(IInputObserver *state)
{
    subscriptions.push_back(state);
}

void Game::InputManager::unsubscribe(IInputObserver *state)
{
    subscriptions.remove(state);
}

void Game::InputManager::notify()
{
    for (auto it : subscriptions)
    {
        it->handleInput(*this->event);
    }
}

Game::InputEvent *Game::InputManager::handleInput(SDL_Event *event)
{
    type = InputType::OTHER;
    switch (event->type)
    {
    case SDL_EventType::SDL_EVENT_KEY_DOWN:
        type = InputType::KEY_PRESSED;
        break;
    case SDL_EventType::SDL_EVENT_KEY_UP:
        type = InputType::KEY_RELEASED;
        break;
    case SDL_EventType::SDL_EVENT_JOYSTICK_BUTTON_DOWN:
        type = InputType::CONTROLLER_BUTTON_PRESSED;
        break;
    case SDL_EventType::SDL_EVENT_JOYSTICK_BUTTON_UP:
        type = InputType::CONTROLLER_BUTTON_RELEASED;
        break;
    case SDL_EventType::SDL_EVENT_JOYSTICK_AXIS_MOTION:
        type = InputType::CONTROLLER_AXIS;
        break;
    case SDL_EventType::SDL_EVENT_MOUSE_MOTION:
        type = InputType::MOUSE_MOVED;
        break;
    case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN:
        type = InputType::CONTROLLER_BUTTON_PRESSED;
        break;
    case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_UP:
        type = InputType::CONTROLLER_BUTTON_RELEASED;
        break;
    }
    this->event = new InputEvent(type, event->key.key);
    notify();
    return this->event;
}
