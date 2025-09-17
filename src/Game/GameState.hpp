#pragma once

#include <SDL3/SDL.h>
#include "Input/InputEvent.hpp"

class GameState
{

protected:
	SDL_Window *m_window;
	SDL_Surface *m_screenSurface;

public:
	GameState(SDL_Window *m_window,
			  SDL_Surface *m_screenSurface);
	virtual ~GameState() = default;
	virtual void enter() = 0;		   // Al entrar al estado
	virtual void exit() = 0;		   // Al salir del estado
	virtual void update(const float &dt) = 0; // Lógica del estado
	virtual void render() = 0;		   // Renderizado del estado
	virtual void handleInput(const InputEvent &event) = 0;
};
