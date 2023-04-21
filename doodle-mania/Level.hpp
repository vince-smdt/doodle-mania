#pragma once
#include <SFML/Audio.hpp>
#include <cassert>
#include <queue>

#include "bulletSpawn.hpp"

class Level {
private:
    unsigned int _numberOfTracks;
    int _speed;
    sf::Music _music;
    std::queue<BulletSpawn> _bulletSpawns;

public:
    Level(unsigned int numOfTracks, int speed);
    void PlayMusic();
    void LoadMusic(const char* filePath, float volume);

    unsigned int GetNumberOfTracks();
    int GetSpeed();
    std::queue<BulletSpawn>& GetBulletSpawns();
};

Level::Level(unsigned int numOfTracks, int speed)
    : _numberOfTracks(numOfTracks)
    , _speed(speed)
{}

void Level::PlayMusic()
{
    _music.play();
}

void Level::LoadMusic(const char* filePath, float volume)
{
    _music.openFromFile(filePath);
    _music.setVolume(volume);
}

unsigned int Level::GetNumberOfTracks()
{
    return _numberOfTracks;
}

int Level::GetSpeed()
{
    return _speed;
}

std::queue<BulletSpawn>& Level::GetBulletSpawns()
{
    return _bulletSpawns;
}
