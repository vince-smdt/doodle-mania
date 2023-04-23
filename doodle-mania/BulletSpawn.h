#pragma once
#include <SFML/Graphics.hpp>

class BulletSpawn {
private:
    int _spawnTime;        // In milliseconds
    int _track;            // Track position index
    int _speed;            // Bullet speed
    sf::Color _color;      // Bullet color

public:
    BulletSpawn(int spawnTime, int track, int speed, sf::Color color);

    int GetSpawnTime() const;
    int GetTrack() const;
    int GetSpeed() const;
    sf::Color GetColor() const;
};
