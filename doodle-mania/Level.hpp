#pragma once
#include <SFML/Audio.hpp>
#include <cassert>
#include <queue>

#include "bulletSpawn.hpp"
#include "utils.h"

class Level {
private:
    unsigned int _numberOfTracks;
    int _speed;
    sf::Music _music;
    std::queue<BulletSpawn> _bulletSpawns;

public:
    Level();
    void PlayMusic();
    void LoadMusic(const char* filePath, float volume);
    void GenerateLevelFromFile(const char* filePath);

    unsigned int GetNumberOfTracks();
    int GetSpeed();
    std::queue<BulletSpawn>& GetBulletSpawns();
};

Level::Level()
    : _numberOfTracks(7)
    , _speed(10)
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

void Level::GenerateLevelFromFile(const char* filePath)
{
    std::ifstream level(filePath);

    std::string line;
    std::vector<std::string> params;

    if (!level) std::cout << "Erreur de chargement du fichier '" << filePath << "'.";

    while (!_bulletSpawns.empty()) _bulletSpawns.pop();

    while (level.good()) {

        // Read command line from level text file
        getline(level, line);

        // Split command line into params
        split_string(line, params);

        // Tolower string
        for (auto& c : params[0]) c = tolower(c);

        // Command interpreter
        if (params[0] == "spawn")
        {
            assert(params.size() == 3);

            int time = stoi(params[1]) - (1000.0 / (60.0 * _speed)) * 1000;

            for (int i = 0; i < _numberOfTracks; i++)
                if (params[2][i] == '#' || params[2][i] == '%')
                    _bulletSpawns.push({ time, i, _speed, {255, 40, 40} });
        }
        else if (params[0] == "speed")
        {
            assert(params.size() == 2);

            _speed = stoi(params[1]);
        }
    }
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
