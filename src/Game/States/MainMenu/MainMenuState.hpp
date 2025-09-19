#pragma once

#include <memory>
#include "Game/GameState.hpp"
#include <SDL3_ttf/SDL_ttf.h>

namespace Game
{
	class MainMenuState : public Game::GameState
	{
	private:
        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_font;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_title;

		void startNewGame();
		void exitGame();
		void moveMenuUp();
		void moveMenuDown();

	public:
		MainMenuState(SDL_Renderer *renderer);
		void enter() override;
		void exit() override;
		void update(const float &dt) override;
		void render() override;
		bool load() override;
		void handleInput(const InputEvent &event) override;
	};
}
