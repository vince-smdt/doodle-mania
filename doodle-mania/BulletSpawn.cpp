#include "BulletSpawn.h"

BulletSpawn::BulletSpawn(int spawnTime, int track, int speed, sf::Color color)
{
    _spawnTime = spawnTime;
    _track = track;
    _speed = speed;
    _color = color;
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
