#include "InputManager.hpp"

Game::InputManager::~InputManager()
{
    if (event)
    {
        delete event;
        event = nullptr;
    }
    // No eliminar los observers, solo limpiar la lista
    subscriptions.clear();
}

void Game::InputManager::subscribe(IInputObserver *state)
{
    subscriptions.push_back(state);
}

void Game::InputManager::unsubscribe(IInputObserver *state)
{
    subscriptions.remove(state);
}

Game::Vector2 Game::InputManager::getMousePos(SDL_Event *event, Vector2 *relPos)
{
    Vector2 pos = Vector2(event->motion.x, event->motion.y);
    if (relPos)
    {
        relPos->x = event->motion.xrel;
        relPos->y = event->motion.yrel;
    }
    return pos;
}

void Game::InputManager::notify()
{
    for (auto it : subscriptions)
    {
        SDL_Log("Event: [%f, %f] (%f, %f)", event->mouse_pos.x, event->mouse_pos.y, event->mouse_rel.y, event->mouse_rel.y);
        if (event->type == InputType::MOUSE_MOVED)
            continue;
        it->handleInput(*this->event);
    }
}

bool Game::InputManager::isInputEvent(Uint32 type_)
{
    // Ignore any other non Input Events
    SDL_EventType type = static_cast<SDL_EventType>(type_);
    return type == SDL_EVENT_KEY_DOWN ||
           type == SDL_EVENT_KEY_UP ||
           type == SDL_EVENT_GAMEPAD_BUTTON_DOWN ||
           type == SDL_EVENT_GAMEPAD_BUTTON_UP ||
           type == SDL_EVENT_JOYSTICK_BUTTON_DOWN ||
           type == SDL_EVENT_JOYSTICK_BUTTON_UP ||
           type == SDL_EVENT_MOUSE_MOTION ||
           type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
           type == SDL_EVENT_MOUSE_BUTTON_UP;
}

bool Game::InputManager::isAddedEvent(Uint32 type_)
{
    SDL_EventType type = static_cast<SDL_EventType>(type_);
    return type == SDL_EVENT_JOYSTICK_ADDED ||
           type == SDL_EVENT_JOYSTICK_REMOVED ||
           type == SDL_EVENT_GAMEPAD_ADDED ||
           type == SDL_EVENT_GAMEPAD_REMOVED;
}

void Game::InputManager::handleInput(SDL_Event *event)
{
    if (!isInputEvent(event->type))
        return;

    if (this->event)
    {
        delete this->event;
        this->event = nullptr;
    }

    type = InputType::OTHER;
    switch (event->type)
    {
    case SDL_EventType::SDL_EVENT_KEY_DOWN:
        type = InputType::KEY_PRESSED;
        break;
    case SDL_EventType::SDL_EVENT_KEY_UP:
        type = InputType::KEY_RELEASED;
        break;
    case SDL_EventType::SDL_EVENT_GAMEPAD_BUTTON_DOWN:
    case SDL_EventType::SDL_EVENT_JOYSTICK_BUTTON_DOWN:
        type = InputType::CONTROLLER_BUTTON_PRESSED;
        break;
    case SDL_EventType::SDL_EVENT_GAMEPAD_BUTTON_UP:
    case SDL_EventType::SDL_EVENT_JOYSTICK_BUTTON_UP:
        type = InputType::CONTROLLER_BUTTON_RELEASED;
        break;
    case SDL_EventType::SDL_EVENT_GAMEPAD_AXIS_MOTION:
    case SDL_EventType::SDL_EVENT_JOYSTICK_AXIS_MOTION:
        type = InputType::CONTROLLER_AXIS;
        break;
    // case SDL_EventType::SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
    case SDL_EventType::SDL_EVENT_MOUSE_MOTION:
        type = InputType::MOUSE_MOVED;
        break;
    // case SDL_EventType::SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
    case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN:
        type = InputType::MOUSE_PRESSED;
        break;
    // case SDL_EventType::SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
    case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_UP:
        type = InputType::MOUSE_RELEASED;
        break;
    }

    // Manejo de eventos de gamepad
    if (type == InputType::CONTROLLER_AXIS)
    {
        this->event = new InputEvent(type, static_cast<SDL_GamepadAxis>(event->gaxis.axis));
    }
    else if (
        type == InputType::CONTROLLER_BUTTON_PRESSED ||
        type == InputType::CONTROLLER_BUTTON_RELEASED)
    {
        this->event = new InputEvent(type, static_cast<SDL_GamepadButton>(event->gbutton.button));
    }
    else if (type == InputType::MOUSE_MOVED)
    {
        // Manejo de eventos de mouse
        Vector2 rel = Vector2();
        Vector2 pos = getMousePos(event, &rel);
        this->event = new InputEvent(type, pos, rel);
    }
    else if (
        type == InputType::MOUSE_PRESSED ||
        type == InputType::MOUSE_RELEASED)
    {
        Vector2 rel = Vector2();
        Vector2 pos = getMousePos(event);
        this->event = new InputEvent(type, pos, rel, event->button.button);
    }
    else if (
        type == InputType::KEY_PRESSED ||
        type == InputType::KEY_RELEASED)
    {
        // Manejo de eventos de teclado
        this->event = new InputEvent(type, event->key.key);
    }
    if (this->event)
        notify();
    return;
}

void Game::InputManager::handleDevice(SDL_Event *event)
{
    if (!isAddedEvent(event->type))
        return;

    // Configure added device
}
