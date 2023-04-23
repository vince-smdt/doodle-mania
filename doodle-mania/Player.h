#pragma once
#include <SFML/Graphics.hpp>

#include "Flashable.h"
#include "SmoothMovementDelegate.h"

class Player : public sf::CircleShape
             , public Flashable
             , public SmoothMovementDelegate
{
public:
    enum Direction { NONE, LEFT, RIGHT };

    Player();

    void Hit();
    bool IsHit() const;
};
