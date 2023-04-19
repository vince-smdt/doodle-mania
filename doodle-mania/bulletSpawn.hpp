#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class BulletSpawn {
private:
    int _spawnTime;        // In milliseconds
    int _track;            // Which track index
    int _speed;            // Bullet speed
    Color _color;        // Bullet color

public:

    // Constructers
    BulletSpawn();
    BulletSpawn(int spawnTime, int track, int speed, Color color);
    ~BulletSpawn();

    // Getters
    int getSpawnTime()const;
    int getTrack()const;
    int getSpeed()const;
    Color getColor()const;

};

BulletSpawn::BulletSpawn() 
{
    _spawnTime = 0;
    _track = 0;
    _speed = 0;
}

BulletSpawn::BulletSpawn(int spawnTime, int track, int speed, Color color) 
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

int BulletSpawn::getSpawnTime()const 
{
    return _spawnTime;
}

int BulletSpawn::getTrack()const 
{
    return _track;
}

int BulletSpawn::getSpeed()const 
{
    return _speed;
}

Color BulletSpawn::getColor()const 
{
    return _color;
}