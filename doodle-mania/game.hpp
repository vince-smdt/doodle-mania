#pragma once
#include <SFML/Graphics.hpp>
#include <list>

#include "bullet.hpp"
#include "Level.hpp"
#include "LevelGenerator.hpp"
#include "player.hpp"

#define TRACKS_DIST_APART 70

using namespace sf;

class Game {
private:
    RenderWindow* _window;

    std::shared_ptr<Level> _level;

    Player _player;
    int _playerTrackPos;

    std::list<Bullet> _bullets;
    Clock _bulletSpawnClock;

    std::vector<RectangleShape> _tracks;
    RectangleShape _playerLine;
    RectangleShape _background;

public:
    // Constructor
    Game(RenderWindow& window);

    // Init methods and play
    void init();
    void play();

    // Bullet methods
    void moveBullets(int speed);                // move all bullets
    void spawnBullets();                        // Spawn bullets that are ready to spawn with _bulletSpawns
    bool checkBulletCollision()const;            // Check if player is colliding with any bullets
    void deleteOffscreenBullets();                // Delete all bullets that are offscreen

    // Draw methods
    void drawAll();
    void drawTracks();
    void drawBullets();
};

Game::Game(RenderWindow& window) 
{
    _window = &window;
    init();
}

void Game::init()
{
    _level = LevelGenerator::GenerateFromFile("levels/testcopy.txt");

    _playerTrackPos = _level->GetNumberOfTracks() / 2;

    // Initialise tracks
    _tracks.resize(_level->GetNumberOfTracks());
    for (__int64 i = 0; i < _level->GetNumberOfTracks(); i++)
    {
        _tracks[i].setSize(Vector2f(4, _window->getSize().y));
        _tracks[i].setOrigin(Vector2f(2, _tracks[i].getSize().y));
        _tracks[i].setPosition(Vector2f(((_window->getSize().x / 2) - (floor(_tracks.size() / 2) * TRACKS_DIST_APART)) + (i * TRACKS_DIST_APART), _tracks[i].getSize().y));
        _tracks[i].setFillColor(Color(100, 100, 100));
    }

    // Initialise background
    _background.setFillColor(Color(255, 255, 255));
    _background.setSize(Vector2f(_window->getSize().x, _window->getSize().y));
    _background.setPosition(Vector2f(0, 0));

    // Initialise additional shapes
    _playerLine.setFillColor(Color(100, 100, 100));
    _playerLine.setSize(Vector2f(TRACKS_DIST_APART * (_tracks.size() - 1), 4));
    _playerLine.setOrigin(Vector2f(_playerLine.getSize().x / 2, _playerLine.getSize().y / 2));
    _playerLine.setPosition(Vector2f(_window->getSize().x / 2, _window->getSize().y / 1.2));

    // Initialise player position
    _player.InstantlyMoveTo(_tracks[_playerTrackPos].getPosition().x, _playerLine.getPosition().y);
}

void Game::play() 
{
    Event event;

    _level->LoadMusic("music/Boogie Vice - Enter The Rave.wav", 50);
    _level->PlayMusic();

    _bulletSpawnClock.restart();

    while (_window->isOpen()) {
        while (_window->pollEvent(event)) {
            if (event.type == Event::Closed)
                _window->close();
            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                case Keyboard::Left:
                    if (_playerTrackPos > 0) {
                        _playerTrackPos--;
                        _player.MoveTo(_tracks[_playerTrackPos].getPosition().x, _player.getPosition().y);
                    }
                    break;
                case Keyboard::Right:
                    if (_playerTrackPos < _level->GetNumberOfTracks() - 1) {
                        _playerTrackPos++;
                        _player.MoveTo(_tracks[_playerTrackPos].getPosition().x, _player.getPosition().y);
                    }
                    break;
                }
            }
        }

        // Update player states
        _player.UpdateFlashState();
        _player.UpdateMoveState();

        // Handle bullets
        moveBullets(_level->GetSpeed());
        deleteOffscreenBullets();
        spawnBullets();

        // Check if player is hit by bullet
        if (checkBulletCollision() && !_player.IsHit())
            _player.Hit();

        // Draw method
        drawAll();

        _player.rotate(1); // test
    }
}

void Game::moveBullets(int speed) 
{
    for (auto& bullet : _bullets)
    {
        bullet.InstantlyMove(Vector2f(0.0f, bullet.getSpeed()));
    }
}

void Game::spawnBullets() 
{
    while (!_level->GetBulletSpawns().empty() && _level->GetBulletSpawns().front().getSpawnTime() <= _bulletSpawnClock.getElapsedTime().asMilliseconds())
    {
        int trackNum = _level->GetBulletSpawns().front().getTrack();
        float posX = _tracks[trackNum].getPosition().x;
        float speed = _level->GetBulletSpawns().front().getSpeed();
        Color bColor = _level->GetBulletSpawns().front().getColor();

        _bullets.emplace_back(posX, -325.0f, trackNum, speed, bColor);
        _level->GetBulletSpawns().pop();
    }
}

bool Game::checkBulletCollision() const 
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

void Game::deleteOffscreenBullets() 
{
    while (!_bullets.empty() && _bullets.front().getPosition().y > 850)
        _bullets.erase(_bullets.begin());
}

void Game::drawAll() 
{
    _window->clear();

    _window->draw(_background);    // Background
    drawTracks();                  // Tracks
    drawBullets();                 // Bullets
    _window->draw(_playerLine);    // Other lines and shapes
    if (_player.Visible())
        _window->draw(_player);

    _window->display();
}

void Game::drawTracks() 
{
    for (int i = 0; i < _level->GetNumberOfTracks(); i++) _window->draw(_tracks[i]);
}

void Game::drawBullets() 
{
    for (auto& bullet : _bullets) _window->draw(bullet);
}