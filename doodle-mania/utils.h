#pragma once
#include <vector>
#include <iostream>

std::vector<std::string> split_string(std::string s, std::vector<std::string>& vec)
{
    vec.clear();

    size_t pos = 0;
    while ((pos = s.find(' ')) != std::string::npos) {
        vec.push_back(s.substr(0, pos));
        s.erase(0, pos + 1);
    }

    if (!s.empty()) vec.push_back(s.substr(0, pos));

    return vec;
}
