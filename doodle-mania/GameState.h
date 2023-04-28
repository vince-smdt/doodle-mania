#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "Bullet.h"
#include "LevelGenerator.h"
#include "Player.h"
#include "State/State.hpp"

// Forward declarations
struct GameData;
class Level;

class GameState : public State
{
private:
    static const int TRACKS_DIST_APART = 70;

    std::shared_ptr<GameData> _data;

    std::shared_ptr<Level> _level;

    Player _player;
    int _playerTrackPos;

    std::list<Bullet> _bullets;
    sf::Clock _bulletSpawnClock;

    std::vector<sf::RectangleShape> _tracks;
    sf::RectangleShape _playerLine;
    sf::RectangleShape _background;

public:
    GameState(std::shared_ptr<GameData> data);

    void Init() override;
    void HandleInput(sf::Event event) override;
    void Update(float delta) override;
    void Draw(float delta) const override;

    void MoveBullets();
    void SpawnBullets();
    bool PlayerCollidesWithBullet() const;
    void DeleteOffscreenBullets();
};
