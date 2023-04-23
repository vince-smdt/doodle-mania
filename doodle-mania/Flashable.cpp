#include "Flashable.h"

Flashable::Flashable()
    : _flashing(false)
    , _flashes(0)
    , _frequency(0)
    , _visible(true)
{}

void Flashable::Flash(unsigned int flashes, float frequency)
{
    _flashing = true;
    _flashes = flashes;
    _frequency = frequency;
    _clock.restart();
}

bool Flashable::Flashing() const
{
    return _flashing;
}

bool Flashable::Visible() const
{
    return _visible;
}

void Flashable::UpdateFlashState()
{
    sf::Time time = _clock.getElapsedTime();

    if (_flashing && time.asMilliseconds() >= _frequency)
    {
        if (!_visible && --_flashes == 0)
        {
            _flashing = false;
        }

        _visible = !_visible;
        _clock.restart();
    }
}
