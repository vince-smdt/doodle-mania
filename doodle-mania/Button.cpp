#include "Button.h"

void Button::SetColor(sf::Color color)
{
    _shape.setFillColor(color);
}

void Button::SetFont(sf::Font& font)
{
    _text.setFont(font);
}

void Button::SetFontColor(sf::Color color)
{
    _text.setFillColor(color);
}

void Button::SetFontSize(unsigned int size)
{
    _text.setCharacterSize(size);
    CenterOrigins();
}

void Button::SetOutlineColor(sf::Color color)
{
    _shape.setOutlineColor(color);
}

void Button::SetOutlineThickness(unsigned int thickness)
{
    _shape.setOutlineThickness(thickness);
}

void Button::SetPosition(sf::Vector2f pos)
{
    _shape.setPosition(pos);
    _text.setPosition(pos);
}

void Button::SetText(sf::String text)
{
    _text.setString(text);
    CenterOrigins();
}

void Button::SetSize(sf::Vector2f size)
{
    _shape.setSize(size);
    CenterOrigins();
}

bool Button::MouseHovering(const sf::RenderWindow& window) const
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return _shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::Draw(sf::RenderWindow& window) const
{
    window.draw(_shape);
    window.draw(_text);
}

void Button::CenterOrigins()
{
    sf::Vector2f box = _shape.getSize();
    _shape.setOrigin(box.x / 2, box.y / 2);

    sf::FloatRect bounds = _text.getLocalBounds();
    _text.setOrigin(bounds.left + bounds.width / 2, bounds.top + MaxCharHeight() / 2);
}

float Button::MaxCharHeight()
{
    const sf::String* textString = &_text.getString();
    unsigned int textCharSize = _text.getCharacterSize();
    bool textIsBold = _text.getStyle() & sf::Text::Bold;

    float currentHeight,
          maxHeight = 0;

    for (size_t i = 0; i < textString->getSize(); ++i)
    {
        currentHeight = _text.getFont()->getGlyph((*textString)[i], textCharSize, textIsBold).bounds.height;
        if (currentHeight > maxHeight)
        {
            maxHeight = currentHeight;
        }
    }

    return maxHeight;
}
