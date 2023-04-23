#pragma once
#include <SFML/Audio.hpp>
#include <cassert>
#include <queue>

#include "BulletSpawn.h"

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
