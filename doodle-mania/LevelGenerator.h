#pragma once
#include <fstream>
#include <iostream>
#include <memory>

// Forward declarations
class Level;

namespace LevelGenerator
{
    static std::shared_ptr<Level> level;
    static std::vector<std::string> params;

    std::shared_ptr<Level> GenerateFromFile(const char* filePath);
    void ProcessCommand();
    void CreateBulletSpawn();
};
