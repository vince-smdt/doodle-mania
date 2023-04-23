#pragma once
#include <SFML/Graphics.hpp>

class SmoothMovementDelegate
{
private:
    sf::Vector2f _aimPos;
    sf::Transformable* _entity;
    float _easeInRate;

protected:
    SmoothMovementDelegate(sf::Transformable* entity);

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
