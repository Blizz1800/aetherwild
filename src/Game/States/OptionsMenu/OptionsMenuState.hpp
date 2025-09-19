#pragma once

#include <memory>
#include "Game/GameState.hpp"
#include <SDL3_ttf/SDL_ttf.h>

namespace Game
{
    class OptionsMenuState : public GameState
    {
    public:
        OptionsMenuState(SDL_Renderer* renderer);
        ~OptionsMenuState() override;

        bool load() override;
        void enter() override {};
        void exit() override {};
        void update(const float& dt) override {};
        void render() override;
        void handleInput(const InputEvent& event) override;

    private:
        std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_font;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_title;
        bool m_loaded;
    };
}