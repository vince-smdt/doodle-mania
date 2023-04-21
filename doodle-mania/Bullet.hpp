#pragma once
#include <SFML/Graphics.hpp>

#include "Movable.hpp"

#define BULLET_RADIUS 16

class Bullet : public sf::CircleShape
             , public Movable
{
private:
    int _trackPos;        // Track number the bullet is positioned on
    float _speed;

protected:
    void OnMoveEvent(Movable::Event event) override;

public:
    // Constructers
    Bullet(float posX, float posY, int trackPos, float speed, sf::Color color);

    int getTrackPos() const;
    float getSpeed() const;
};

Bullet::Bullet(float posX, float posY, int trackPos, float speed, sf::Color color) 
    : Movable(this)
    , _trackPos(trackPos)
    , _speed(speed)
{
    setRadius(BULLET_RADIUS);
    setOrigin(sf::Vector2f(getRadius(), getRadius()));
    setFillColor(color);
    setOutlineThickness(5);
    setOutlineColor(sf::Color::Black);

    move(posX, posY);
}

void Bullet::OnMoveEvent(Movable::Event event)
{
}

int Bullet::getTrackPos()const 
{
    return _trackPos;
}

float Bullet::getSpeed() const
{
    return _speed;
}
