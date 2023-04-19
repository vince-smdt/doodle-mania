#pragma once
#include <SFML/Graphics.hpp>

#include "Movable.hpp"

class Bullet : public Movable
{
private:
    sf::CircleShape _shape;
    int _trackPos;        // Track number the bullet is positioned on
    float _speed;

protected:
    void OnMoveEvent(Movable::Event event) override;

public:
    // Constructers
    Bullet(float posX, float posY, int trackPos, float speed, sf::Color color);

    // Init, draw and move
    void draw(sf::RenderWindow& window);

    //Set
    void setRadius(float radius);
    void setScale(sf::Vector2f vector);

    //Get
    int getRadius() const;
    int getTrackPos() const;
    float getSpeed() const;
};

Bullet::Bullet(float posX, float posY, int trackPos, float speed, sf::Color color) 
    : Movable(&_shape)
    , _trackPos(trackPos)
    , _speed(speed)
{
    _shape.setRadius(16);
    _shape.setOrigin(sf::Vector2f(_shape.getRadius(), _shape.getRadius()));
    _shape.setFillColor(color);
    _shape.setOutlineThickness(5);
    _shape.setOutlineColor(sf::Color::Black);

    InstantlyMoveTo({ posX, posY });
}

void Bullet::OnMoveEvent(Movable::Event event)
{
}

void Bullet::draw(sf::RenderWindow& window) 
{
    window.draw(_shape);
}

void Bullet::setRadius(float radius) 
{
    _shape.setRadius(radius);
}

void Bullet::setScale(sf::Vector2f vector) 
{
    _shape.setScale(vector);
}

int Bullet::getRadius()const 
{
    return _shape.getRadius();
}

int Bullet::getTrackPos()const 
{
    return _trackPos;
}

float Bullet::getSpeed() const
{
    return _speed;
}
