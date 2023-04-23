#include "Bullet.h"

Bullet::Bullet(float posX, float posY, int trackPos, float speed, sf::Color color)
    : _trackPos(trackPos)
    , _speed(speed)
{
    setRadius(BULLET_RADIUS);
    setOrigin(sf::Vector2f(getRadius(), getRadius()));
    setFillColor(color);
    setOutlineThickness(5);
    setOutlineColor(sf::Color::Black);
    setPosition(posX, posY);
}

int Bullet::GetTrackPos()const
{
    return _trackPos;
}

float Bullet::GetSpeed() const
{
    return _speed;
}
