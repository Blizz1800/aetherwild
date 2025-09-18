#pragma once

#include <SDL3/SDL.h>

namespace Game
{
	enum class InputType
	{
		KEY_PRESSED,
		KEY_RELEASED,
		MOUSE_PRESSED,
		MOUSE_RELEASED,
		MOUSE_MOVED,
		CONTROLLER_BUTTON,
		CONTROLLER_AXIS
	};

	struct InputEvent
	{
		InputType type;

		// Para teclado
		SDL_Keycode key;

		// Para mouse
		int mouseX, mouseY;
		int mouseButton;

		// Para gamepad
		int controllerButton;
		float axisValue;

		// Constructor para teclas
		InputEvent(InputType t, SDL_Keycode k)
			: type(t), key(k) {}

		// Constructor para mouse
		InputEvent(InputType t, int x, int y, int btn = -1)
			: type(t), mouseX(x), mouseY(y), mouseButton(btn) {}
	};
}