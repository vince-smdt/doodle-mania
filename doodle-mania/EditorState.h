#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"
#include "State/State.hpp"

// Forward declarations
struct GameData;

class EditorState : public State
{
// Public interface
public:
    EditorState(std::shared_ptr<GameData> data);

    void Init() override;
    void HandleInput(sf::Event event) override;
    void Update(float delta) override;
    void Draw(float delta) const override;

// Private properties
private:
    std::shared_ptr<GameData> _data;

    Button _backButton;
};