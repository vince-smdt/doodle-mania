#pragma once
#include <SFML/Graphics.hpp>

class Flashable
{
private:
    bool _flashing;
    unsigned int _flashes;
    float _frequency;
    bool _visible;
    sf::Clock _clock;

protected:
    Flashable();

public:
    void Flash(unsigned int flashes, float frequency);
    bool Flashing() const;
    bool Visible() const;
    void UpdateFlashState();
};
