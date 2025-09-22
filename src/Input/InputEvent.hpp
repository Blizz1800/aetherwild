#pragma once

#include <SDL3/SDL.h>
#include "Utils/Vector2.hpp"

namespace Game
{
	enum class InputType
	{
		KEY_PRESSED,
		KEY_RELEASED,
		MOUSE_PRESSED,
		MOUSE_RELEASED,
		MOUSE_MOVED,
		CONTROLLER_BUTTON_PRESSED,
		CONTROLLER_BUTTON_RELEASED,
		CONTROLLER_AXIS,
		OTHER
	};

	struct InputEvent
	{
		InputType type;

		// Para teclado
		SDL_Keycode key;

		// Para mouse
		Vector2 mouse_pos, mouse_rel;
		int mouseButton;

		// Para gamepad
		SDL_GamepadButton controllerButton;
		SDL_GamepadAxis axisValue;

		// Constructor para teclas
		InputEvent(InputType t, SDL_Keycode k)
			: type(t), key(k) {}

		// Constructor para mouse
		InputEvent(InputType t, Vector2 pos, Vector2 rel, int btn = -1)
			: type(t), mouse_pos(pos), mouse_rel(rel), mouseButton(btn) {}

		// Constructor para gamepad
		InputEvent(InputType t, SDL_GamepadButton btn)
			: type(t), controllerButton(btn) {}

		// Constructor para ejes de gamepad
		InputEvent(InputType t, SDL_GamepadAxis axis)
			: type(t), axisValue(axis) {}

	};
}