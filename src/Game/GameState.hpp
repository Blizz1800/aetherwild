#pragma once

#include <SDL3/SDL.h>
#include "Input/InputManager.hpp"

namespace Game
{
	class GameState : public IInputObserver 
	{

	protected:
		SDL_Renderer *m_renderer;

	public:
		GameState(SDL_Renderer *m_renderer)
			: m_renderer(m_renderer) {};
		virtual ~GameState() = default;
		virtual void enter() = 0;				  // Al entrar al estado
		virtual void exit() = 0;				  // Al salir del estado
		virtual void update(const float &dt) = 0; // Lógica del estado
		virtual void render() = 0;				  // Renderizado del estado
		virtual bool load() = 0;				  // Cargar assets
		virtual void handleInput(const InputEvent &event) = 0;
	};
}