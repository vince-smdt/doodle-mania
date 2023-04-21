#pragma once
#include <SFML/Audio.hpp>
#include <cassert>
#include <queue>

#include "bulletSpawn.hpp"

class Level {
private:
    unsigned int _numberOfTracks;
    sf::Music _music;
    std::queue<BulletSpawn> _bulletSpawns;

public:
    Level(unsigned int numOfTracks, int speed);
    void PlayMusic();
    void LoadMusic(const char* filePath, float volume);

    unsigned int GetNumberOfTracks();
    std::queue<BulletSpawn>& GetBulletSpawns();
};

Level::Level(unsigned int numOfTracks, int speed)
    : _numberOfTracks(numOfTracks)
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

std::queue<BulletSpawn>& Level::GetBulletSpawns()
{
    return _bulletSpawns;
}
