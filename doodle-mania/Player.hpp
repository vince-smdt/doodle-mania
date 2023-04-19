#pragma once
#include <SFML/Graphics.hpp>

#include "Flashable.hpp"
#include "Movable.hpp"

class Player : public Flashable
             , public Movable
{
private:
    sf::CircleShape _shape;

protected:
    void OnFlashEvent(Flashable::Event event) override;
    void OnMoveEvent(Movable::Event event) override;

public:
    enum Direction { NONE, LEFT, RIGHT };

    Player();

    // Init and draw
    void Init();
    void Draw(sf::RenderWindow& window) const;

    // Hit
    void Hit();
    bool IsHit() const;

    // Getters
    int GetRadius() const;

    // Debug
    void Spin();
};

Player::Player()
    : Movable(&_shape)
{}

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

void Player::Init() 
{
    _shape.setRadius(20);
    _shape.setOrigin(20, 20);
    _shape.setPointCount(3);
    _shape.setFillColor(sf::Color::White);
    _shape.setOutlineColor(sf::Color::Black);
    _shape.setOutlineThickness(5);
}

void Player::Draw(sf::RenderWindow& window) const
{
    if (Visible())
    {
        window.draw(_shape);
    }
}

int Player::GetRadius()const 
{
    return _shape.getRadius();
}

void Player::Spin() {
    _shape.rotate(1);
}