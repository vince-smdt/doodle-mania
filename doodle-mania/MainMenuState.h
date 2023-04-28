#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "State/State.hpp"

// Forward declarations
struct GameData;

class MainMenuState : public State
{
public:
    MainMenuState(std::shared_ptr<GameData> data);

    void Init() override;
    void HandleInput(sf::Event event) override;
    void Update(float delta) override;
    void Draw(float delta) const override;

private:
    std::shared_ptr<GameData> _data;

    Button _playButton;
    sf::RectangleShape _background;
};