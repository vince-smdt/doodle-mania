#pragma once
#include <SFML/Graphics.hpp>

class BulletSpawn {
private:
    int _spawnTime;        // In milliseconds
    int _track;            // Track position index
    int _speed;            // Bullet speed
    sf::Color _color;      // Bullet color

public:

    // Constructers
    BulletSpawn();
    BulletSpawn(int spawnTime, int track, int speed, sf::Color color);
    ~BulletSpawn();

    // Getters
    int GetSpawnTime() const;
    int GetTrack() const;
    int GetSpeed() const;
    sf::Color GetColor() const;

};

BulletSpawn::BulletSpawn() 
{
    _spawnTime = 0;
    _track = 0;
    _speed = 0;
}

BulletSpawn::BulletSpawn(int spawnTime, int track, int speed, sf::Color color)
{
    _spawnTime = spawnTime;
    _track = track;
    _speed = speed;
    _color = color;
}

BulletSpawn::~BulletSpawn() 
{
    _spawnTime = 0;
    _track = 0;
}

int BulletSpawn::GetSpawnTime()const 
{
    return _spawnTime;
}

int BulletSpawn::GetTrack()const 
{
    return _track;
}

int BulletSpawn::GetSpeed()const 
{
    return _speed;
}

sf::Color BulletSpawn::GetColor()const
{
    return _color;
}