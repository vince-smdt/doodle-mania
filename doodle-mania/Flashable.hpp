#pragma once
#include <SFML/Graphics.hpp>

class Flashable
{
private:
    enum class State
    {
        VISIBLE,
        HIDDEN
    };

    bool _flashing;
    unsigned int _flashes;
    float _frequency;
    State _state;
    sf::Clock _clock;

protected:
    enum class Event
    {
        NONE,
        SHOW,
        HIDE,
        START,
        STOP
    };

    Flashable();
    virtual void OnFlashEvent(Event event) = 0;

public:
    void Flash(unsigned int flashes, float frequency);
    bool Flashing() const;
    bool Visible() const;
    void UpdateFlashState();
};

Flashable::Flashable()
    : _flashing(false)
    , _flashes(0)
    , _frequency(0)
    , _state(State::VISIBLE)
{}

void Flashable::Flash(unsigned int flashes, float frequency)
{
    _flashing = true;
    _flashes = flashes;
    _frequency = frequency;
    _clock.restart();
    OnFlashEvent(Event::START);
}

bool Flashable::Flashing() const
{
    return _flashing;
}

bool Flashable::Visible() const
{
    return _state == State::VISIBLE;
}

void Flashable::UpdateFlashState()
{
    Event event = Event::NONE;
    sf::Time time = _clock.getElapsedTime();

    if (!_flashing || time.asMilliseconds() < _frequency)
    {
        event = Event::NONE;
    }
    else if (_state == State::VISIBLE)
    {
        _state = State::HIDDEN;
        event = Event::HIDE;
        _clock.restart();
    }
    else if (_state == State::HIDDEN)
    {
        _state = State::VISIBLE;

        if (--_flashes == 0)
        {
            event = Event::STOP;
            _flashing = false;
        }
        else
        {
            event = Event::SHOW;
        }

        _clock.restart();
    }

    OnFlashEvent(event);
}
