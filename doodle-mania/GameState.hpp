#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "Bullet.hpp"
#include "Level.hpp"
#include "LevelGenerator.hpp"
#include "Player.hpp"

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
    // Constructor
    GameState(sf::RenderWindow& window);

    // Init methods and play
    void init();
    void play();

    // Bullet methods
    void moveBullets();                     // move all bullets
    void spawnBullets();                    // Spawn bullets that are ready to spawn with _bulletSpawns
    bool PlayerCollidesWithBullet()const;   // Check if player is colliding with any bullets
    void deleteOffscreenBullets();          // Delete all bullets that are offscreen

    // Draw methods
    void draw();
};

GameState::GameState(sf::RenderWindow& window)
{
    _window = &window;
    init();
}

void GameState::init()
{
    _level = LevelGenerator::GenerateFromFile("levels/testcopy.txt");

    _playerTrackPos = _level->GetNumberOfTracks() / 2;

    // Initialise tracks
    _tracks.resize(_level->GetNumberOfTracks());
    for (unsigned int i = 0; i < _level->GetNumberOfTracks(); i++)
    {
        _tracks[i].setSize(sf::Vector2f(4, _window->getSize().y));
        _tracks[i].setOrigin(sf::Vector2f(2, _tracks[i].getSize().y));
        _tracks[i].setPosition(sf::Vector2f(((_window->getSize().x / 2) - (floor(_tracks.size() / 2) * TRACKS_DIST_APART)) + (i * TRACKS_DIST_APART), _tracks[i].getSize().y));
        _tracks[i].setFillColor(sf::Color(100, 100, 100));
    }

    // Initialise background
    _background.setFillColor(sf::Color::White);
    _background.setSize(sf::Vector2f(_window->getSize().x, _window->getSize().y));
    _background.setPosition(sf::Vector2f(0, 0));

    // Initialise additional shapes
    _playerLine.setFillColor(sf::Color(100, 100, 100));
    _playerLine.setSize(sf::Vector2f(TRACKS_DIST_APART * (_tracks.size() - 1), 4));
    _playerLine.setOrigin(sf::Vector2f(_playerLine.getSize().x / 2, _playerLine.getSize().y / 2));
    _playerLine.setPosition(sf::Vector2f(_window->getSize().x / 2, _window->getSize().y / 1.2));

    // Initialise player position
    _player.InstantlyMoveTo(_tracks[_playerTrackPos].getPosition().x, _playerLine.getPosition().y);
}

void GameState::play()
{
    sf::Event event;

    _level->LoadMusic("music/Boogie Vice - Enter The Rave.wav", 50);
    _level->PlayMusic();

    _bulletSpawnClock.restart();

    while (_window->isOpen()) {
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                    {
                        if (_playerTrackPos > 0) {
                            _playerTrackPos--;
                            _player.MoveTo(_tracks[_playerTrackPos].getPosition().x, _player.getPosition().y);
                        }
                        break;
                    }
                    case sf::Keyboard::Right:
                    {
                        if (_playerTrackPos < _level->GetNumberOfTracks() - 1) {
                            _playerTrackPos++;
                            _player.MoveTo(_tracks[_playerTrackPos].getPosition().x, _player.getPosition().y);
                        }
                        break;
                    }
                }
            }
        }

        // Update player states
        _player.UpdateFlashState();
        _player.UpdateMoveState();

        // Handle bullets
        moveBullets();
        deleteOffscreenBullets();
        spawnBullets();

        // Check if player is hit by bullet
        if (PlayerCollidesWithBullet() && !_player.IsHit())
            _player.Hit();

        _player.rotate(1);

        // Draw method
        draw();
    }
}

void GameState::moveBullets()
{
    for (auto& bullet : _bullets)
    {
        bullet.move(0.0f, bullet.getSpeed());
    }
}

void GameState::spawnBullets()
{
    while (!_level->GetBulletSpawns().empty() && _level->GetBulletSpawns().front().getSpawnTime() <= _bulletSpawnClock.getElapsedTime().asMilliseconds())
    {
        int trackNum = _level->GetBulletSpawns().front().getTrack();
        float posX = _tracks[trackNum].getPosition().x;
        float speed = _level->GetBulletSpawns().front().getSpeed();
        sf::Color bColor = _level->GetBulletSpawns().front().getColor();

        _bullets.emplace_back(posX, -325.0f, trackNum, speed, bColor);
        _level->GetBulletSpawns().pop();
    }
}

bool GameState::PlayerCollidesWithBullet() const
{
    for (auto& bullet : _bullets)
    {
        if (bullet.getGlobalBounds().intersects(_player.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}

void GameState::deleteOffscreenBullets()
{
    while (!_bullets.empty() && _bullets.front().getPosition().y > _window->getSize().y + BULLET_RADIUS * 2)
    {
        _bullets.erase(_bullets.begin());
    }
}

void GameState::draw()
{
    _window->clear();

    _window->draw(_background);                             // Background
    for (auto& track : _tracks) _window->draw(track);       // Tracks
    for (auto& bullet : _bullets) _window->draw(bullet);    // Bullets
    _window->draw(_playerLine);                             // Other lines and shapes
    if (_player.Visible()) _window->draw(_player);          // Player

    _window->display();
}
