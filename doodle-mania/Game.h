#pragma once
#include <cassert>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

#include "AssetManager.h"
#include "MainMenuState.h"
#include "InputManager.h"
#include "State/StateMachine.h"

struct GameData
{
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
};

class Game
{
private:
    const float dt = 1.0f / 60.0f;
    sf::Clock _clock;
    std::shared_ptr<GameData> _data;
public:
    Game();
    void Run();
};
