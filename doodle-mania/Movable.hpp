#pragma once
#include <SFML/Graphics.hpp>

class Movable
{
private:
    enum class State
    {
        STOPPED,
        MOVING
    };

    sf::Vector2f _aimPos;
    sf::Transformable* _entity;
    float _speed;
    State _state;

protected:
    enum class Event
    {
        NONE,
        MOVE
    };

    Movable(sf::Transformable* entity);
    virtual void OnMoveEvent(Event event) = 0;

public:
    void Move(sf::Vector2f vector);
    void Move(float x, float y);
    void MoveTo(sf::Vector2f vector);
    void MoveTo(float x, float y);
    void InstantlyMove(sf::Vector2f vector);
    void InstantlyMove(float x, float y);
    void InstantlyMoveTo(sf::Vector2f vector);
    void InstantlyMoveTo(float x, float y);
    void SetSpeed(float speed);
    void UpdateMoveState();
};

Movable::Movable(sf::Transformable* entity)
    : _entity(entity)
    , _state(State::STOPPED)
    , _speed(0.5f)
{}

void Movable::Move(sf::Vector2f vector)
{
    _aimPos += vector;
}

void Movable::Move(float x, float y)
{
    _aimPos += { x, y };
}

void Movable::MoveTo(sf::Vector2f vector)
{
    _aimPos = vector;
}

void Movable::MoveTo(float x, float y)
{
    _aimPos = { x, y };
}

void Movable::InstantlyMove(sf::Vector2f vector)
{
    _aimPos += vector;
    _entity->move(vector);
}

void Movable::InstantlyMove(float x, float y)
{
    _aimPos += { x, y };
    _entity->move(x, y);
}

void Movable::InstantlyMoveTo(sf::Vector2f vector)
{
    _aimPos = vector;
    _entity->setPosition(vector);
}

void Movable::InstantlyMoveTo(float x, float y)
{
    _aimPos = { x, y };
    _entity->setPosition(x, y);
}

void Movable::SetSpeed(float speed)
{
    _speed = speed;
}

void Movable::UpdateMoveState()
{
    sf::Vector2f dist = _aimPos - _entity->getPosition();
    bool moving = _aimPos != _entity->getPosition();
    float rate = 1 / _speed;

    // TODO - round up to certain decimal point to avoid micromovement delaying when MOVE events stop being sent
    _entity->move({ dist.x / rate, dist.y / rate });
    OnMoveEvent(moving ? Event::MOVE : Event::NONE);
}
