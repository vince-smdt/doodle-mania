#pragma once
#include <SFML/Graphics.hpp>

#include "Flashable.hpp"
#include "Movable.hpp"

class Player : public sf::CircleShape
             , public Flashable
             , public Movable
{
protected:
    void OnFlashEvent(Flashable::Event event) override;
    void OnMoveEvent(Movable::Event event) override;

public:
    enum Direction { NONE, LEFT, RIGHT };

    Player();

    void Hit();
    bool IsHit() const;
};

Player::Player()
    : Movable(this)
{
    setRadius(20);
    setOrigin(20, 20);
    setPointCount(3);
    setFillColor(sf::Color::White);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(5);
}

void Player::OnFlashEvent(Flashable::Event event)
{
}

void Player::OnMoveEvent(Movable::Event event)
{
}

void Player::Hit() 
{
    Flash(3, 100.0f);
}

bool Player::IsHit()const 
{
    return Flashing();
}
