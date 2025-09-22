#pragma once
#include <list>

#include "InputEvent.hpp"

namespace Game
{
    class IInputObserver
    {
    public:
        virtual ~IInputObserver() = default;
        virtual void handleInput(const InputEvent &event) = 0;
    };

    class InputManager
    {
    private:
        InputManager(){};
        ~InputManager();
        InputEvent *event = nullptr;
        InputType type;
        std::list<IInputObserver *> subscriptions;

        Vector2 getMousePos(SDL_Event *event, Vector2* relPos = nullptr);
        void notify();
        bool isInputEvent(Uint32 type_);
        bool isAddedEvent(Uint32 type_);

    public:
        InputManager(const InputManager &) = delete;
        InputManager &operator=(const InputManager &) = delete;
        InputManager(InputManager &&) = delete;
        InputManager &operator=(InputManager &&) = delete;

        static InputManager *getInstance()
        {
            static InputManager instance;
            return &instance;
        };

        void subscribe(IInputObserver *state);
        void unsubscribe(IInputObserver *state);

        void handleInput(SDL_Event *event);
        void handleDevice(SDL_Event *event);
    };
}

#define sInputMgr InputManager::getInstance()
