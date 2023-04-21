#pragma once
#include <SFML/Graphics.hpp>

class SmoothMovementDelegate
{
private:
    enum class State
    {
        STOPPED,
        MOVING
    };

    sf::Vector2f _aimPos;
    sf::Transformable* _entity;
    float _easeInRate;
    State _state;

protected:
    enum class Event
    {
        NONE,
        MOVE
    };

    SmoothMovementDelegate(sf::Transformable* entity);
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
    void SetSpeed(float easeInRate);
    void UpdateMoveState();
};

SmoothMovementDelegate::SmoothMovementDelegate(sf::Transformable* entity)
    : _entity(entity)
    , _state(State::STOPPED)
    , _easeInRate(0.5f)
{}

void SmoothMovementDelegate::Move(sf::Vector2f vector)
{
    _aimPos += vector;
}

void SmoothMovementDelegate::Move(float x, float y)
{
    _aimPos += { x, y };
}

void SmoothMovementDelegate::MoveTo(sf::Vector2f vector)
{
    _aimPos = vector;
}

void SmoothMovementDelegate::MoveTo(float x, float y)
{
    _aimPos = { x, y };
}

void SmoothMovementDelegate::InstantlyMove(sf::Vector2f vector)
{
    _aimPos += vector;
    _entity->move(vector);
}

void SmoothMovementDelegate::InstantlyMove(float x, float y)
{
    _aimPos += { x, y };
    _entity->move(x, y);
}

void SmoothMovementDelegate::InstantlyMoveTo(sf::Vector2f vector)
{
    _aimPos = vector;
    _entity->setPosition(vector);
}

void SmoothMovementDelegate::InstantlyMoveTo(float x, float y)
{
    _aimPos = { x, y };
    _entity->setPosition(x, y);
}

void SmoothMovementDelegate::SetSpeed(float easeInRate)
{
    _easeInRate = easeInRate;
}

void SmoothMovementDelegate::UpdateMoveState()
{
    sf::Vector2f dist = _aimPos - _entity->getPosition();
    bool moving = _aimPos != _entity->getPosition();
    float rate = 1 / _easeInRate;

    // TODO - round up to certain decimal point to avoid micromovement delaying when MOVE events stop being sent
    _entity->move({ dist.x / rate, dist.y / rate });
    OnMoveEvent(moving ? Event::MOVE : Event::NONE);
}
