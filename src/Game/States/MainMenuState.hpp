#pragma once

#include "Game/GameState.hpp"

class MainMenuState : public GameState
{
private:
	void startNewGame();
	void exitGame();
	void moveMenuUp();
	void moveMenuDown();

public:
	MainMenuState(SDL_Window *window, SDL_Surface *screenSurface)
		: GameState(window, screenSurface) {}
	void enter() override;
	void exit() override;
	void update(const float &dt) override;
	void render() override;
	void handleInput(const InputEvent &event) override;
};