#pragma once
#include <SFML/Graphics.hpp>

class InputManager
{
public:
    sf::Vector2i getMousePosition(sf::RenderWindow& window) const;
};
