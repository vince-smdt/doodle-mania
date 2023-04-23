#include "Level.h"
#include "LevelGenerator.h"
#include "Utils.h"

std::shared_ptr<Level> LevelGenerator::GenerateFromFile(const char* filePath)
{
    unsigned int numberOfTracks = 7;
    int speed = 10;
    level = std::make_shared<Level>(numberOfTracks, speed);

    std::ifstream file(filePath);

    std::string line;
    params.clear();

    if (!level) std::cout << "File '" << filePath << "' could not be loaded.";

    while (file.good()) {
        getline(file, line);
        SplitString(line, params);
        ProcessCommand();
    }

    return level;
}

void LevelGenerator::ProcessCommand()
{
    std::string& paramName = params[0];
    for (auto& c : paramName) c = tolower(c);

    if (paramName == "spawn") CreateBulletSpawn();
}

void LevelGenerator::CreateBulletSpawn()
{
    assert(params.size() == 4);

    int hitTime = stoi(params[1]);
    std::string bulletLayout = params[2];
    int speed = stoi(params[3]);
    sf::Color color(255, 40, 40);

    assert(bulletLayout.size() == level->GetNumberOfTracks());

    int time = hitTime - (1000.0f / (60.0f * speed)) * 1000;

    for (int i = 0; i < level->GetNumberOfTracks(); i++)
        if (bulletLayout[i] == '#')
            level->GetBulletSpawns().emplace(time, i, speed, color);
}
