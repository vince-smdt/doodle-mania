#pragma once
#include <SFML/Graphics.hpp>

class Button
{
// Public interface
public:
    void SetColor(sf::Color color);
    void SetFont(sf::Font& font);
    void SetFontColor(sf::Color color);
    void SetFontSize(unsigned int size);
    void SetOutlineColor(sf::Color color);
    void SetOutlineThickness(unsigned int thickness);
    void SetPosition(sf::Vector2f pos);
    void SetText(sf::String text);
    void SetSize(sf::Vector2f size);
    
    bool MouseHovering(const sf::RenderWindow& window) const;
    void Draw(sf::RenderWindow& window) const;

// Helper methods
    void CenterOrigins();
    float MaxCharHeight();

// Private properties
private:
    sf::RectangleShape _shape;
    sf::Text _text;
};