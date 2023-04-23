#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::CircleShape
{
private:
    static const int BULLET_RADIUS = 16;

    int _trackPos;
    float _speed;

public:
    Bullet(float posX, float posY, int trackPos, float speed, sf::Color color);

    int GetTrackPos() const;
    float GetSpeed() const;
};
