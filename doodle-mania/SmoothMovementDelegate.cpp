#include "SmoothMovementDelegate.h"

SmoothMovementDelegate::SmoothMovementDelegate(sf::Transformable* entity)
    : _entity(entity)
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
}
