#include "Level.h"

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
