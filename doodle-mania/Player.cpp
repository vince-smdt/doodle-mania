#include "Player.h"

Player::Player()
    : SmoothMovementDelegate(this)
{
    setRadius(20);
    setOrigin(20, 20);
    setPointCount(3);
    setFillColor(sf::Color::White);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(5);
}

void Player::Hit()
{
    Flash(3, 100.0f);
}

bool Player::IsHit()const
{
    return Flashing();
}
