#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Game/GameState.hpp"
namespace Game
{
	class MainMenuState : public Game::GameState
	{
	private:
		TTF_Font *font = nullptr;
		SDL_Texture *title = nullptr;

		void startNewGame();
		void exitGame();
		void moveMenuUp();
		void moveMenuDown();

	public:
		MainMenuState(SDL_Renderer *renderer)
			: GameState(renderer) {}
		void enter() override;
		void exit() override;
		void update(const float &dt) override;
		void render() override;
		bool load() override;
		void handleInput(const InputEvent &event) override;
	};
}
