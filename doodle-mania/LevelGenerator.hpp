#pragma once
#include <fstream>
#include <memory>

#include "Level.hpp"
#include "utils.h"

namespace LevelGenerator {
    static std::shared_ptr<Level> GenerateFromFile(const char* filePath);

};

std::shared_ptr<Level> LevelGenerator::GenerateFromFile(const char* filePath)
{
    unsigned int numberOfTracks = 7;
    int speed = 10;
    std::shared_ptr<Level> level = std::make_shared<Level>(numberOfTracks, speed);

    std::ifstream file(filePath);

    std::string line;
    std::vector<std::string> params;

    if (!level) std::cout << "File '" << filePath << "' could not be loaded.";

    while (file.good()) {

        // Read command line from level text file
        getline(file, line);

        // Split command line into params
        split_string(line, params);

        // Tolower string
        for (auto& c : params[0]) c = tolower(c);

        // Command interpreter
        if (params[0] == "spawn")
        {
            assert(params.size() == 4);

            int time = stoi(params[1]) - (1000.0f / (60.0f * stoi(params[3]))) * 1000;

            for (int i = 0; i < level->GetNumberOfTracks(); i++)
                if (params[2][i] == '#')
                    level->GetBulletSpawns().push({time, i, stoi(params[3]), {255, 40, 40}});
        }
    }

    return level;
}