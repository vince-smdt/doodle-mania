#include "InputManager.h"

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window) const
{
    return sf::Mouse::getPosition(window);
}
