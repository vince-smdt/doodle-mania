#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "Bullet.h"
#include "LevelGenerator.h"
#include "Player.h"

// Forward declarations
class Level;

class GameState {
private:
    static const int TRACKS_DIST_APART = 70;

    sf::RenderWindow* _window;

    std::shared_ptr<Level> _level;

    Player _player;
    int _playerTrackPos;

    std::list<Bullet> _bullets;
    sf::Clock _bulletSpawnClock;

    std::vector<sf::RectangleShape> _tracks;
    sf::RectangleShape _playerLine;
    sf::RectangleShape _background;

public:
    GameState(sf::RenderWindow& window);

    void Init();
    void Play();
    void Draw();

    void MoveBullets();
    void SpawnBullets();
    bool PlayerCollidesWithBullet()const;
    void DeleteOffscreenBullets();
};
