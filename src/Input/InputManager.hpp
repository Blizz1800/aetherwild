#pragma once
#include <list>

#include "InputEvent.hpp"

namespace Game
{
    class IInputObserver
    {
    public:
        virtual void handleInput(const InputEvent &event) = 0;
    };

    class InputManager
    {
    private:
        InputManager(){};
        ~InputManager();
        InputEvent *event;
        InputType *type;
        std::list<IInputObserver *> subscriptions;

        void notify();

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

        InputEvent *handleInput(SDL_Event *event);
    };
}

#define sInputMgr InputManager::getInstance()
