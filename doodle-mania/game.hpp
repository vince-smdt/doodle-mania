#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>

#include "bullet.hpp"
#include "bulletSpawn.hpp"
#include "player.hpp"
#include "utils.h"

#define TRACKS_DIST_APART 70
#define TOTAL_TRACKS 7

using namespace sf;

class Game {
private:
    RenderWindow* _window;

    int _speed;

    Player _player;
    int _playerTrackPos = TOTAL_TRACKS / 2;

    std::list<Bullet> _bullets;
    std::queue<BulletSpawn> _bulletSpawns;
    Clock _bulletSpawnClock;

    std::vector<RectangleShape> _tracks;

    Music _music;

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

    // Level generation from file
    void generateLevelFromFile(const char* filePath);

    // Sound methods
    void loadMusic(const char* filePath, float volume);

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
    // Initialise game attributs
    _speed = 10;    // Speeds under 10 will make many bullets spawn at same y pos at the beginning of song

    // Initialise tracks
    _tracks.resize(TOTAL_TRACKS);
    for (__int64 i = 0; i < TOTAL_TRACKS; i++)
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
    _player.InstantlyMoveTo(_tracks[floor(TOTAL_TRACKS / 2)].getPosition().x, _playerLine.getPosition().y);
}

void Game::play() 
{
    Event event;

    generateLevelFromFile("levels/testcopy.txt");
    loadMusic("music/Boogie Vice - Enter The Rave.wav", 50);

    _music.play();

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
                    if (_playerTrackPos < TOTAL_TRACKS - 1) {
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
        moveBullets(_speed);
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
    while (!_bulletSpawns.empty() && _bulletSpawns.front().getSpawnTime() <= _bulletSpawnClock.getElapsedTime().asMilliseconds())
    {
        int trackNum = _bulletSpawns.front().getTrack();
        float posX = _tracks[trackNum].getPosition().x;
        float speed = _bulletSpawns.front().getSpeed();
        Color bColor = _bulletSpawns.front().getColor();

        _bullets.emplace_back(posX, -325.0f, trackNum, speed, bColor);
        _bulletSpawns.pop();
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

void Game::generateLevelFromFile(const char* filePath) 
{
    std::ifstream level(filePath);

    std::string line;
    std::vector<std::string> params;

    if (!level) std::cout << "Erreur de chargement du fichier '" << filePath << "'.";

    while (!_bulletSpawns.empty()) _bulletSpawns.pop();

    while (level.good()) {

        // Read command line from level text file
        getline(level, line);

        // Split command line into params
        split_string(line, params);

        // Tolower string
        for (auto& c : params[0]) c = tolower(c);

        // Command interpreter
        if (params[0] == "spawn") 
        {
            assert(params.size() == 3);

            int time = stoi(params[1]) - (1000.0 / (60.0 * _speed)) * 1000;

            for (int i = 0; i < TOTAL_TRACKS; i++)
                if (params[2][i] == '#' || params[2][i] == '%')
                    _bulletSpawns.push({ time, i, _speed, {255, 40, 40} });
        }
        else if (params[0] == "speed") 
        {
            assert(params.size() == 2);

            _speed = stoi(params[1]);
        }
    }
}

void Game::loadMusic(const char* filePath, float volume) 
{
    _music.openFromFile(filePath);
    _music.setVolume(volume);
    _music.setLoop(false);
}

void Game::drawAll() 
{
    _window->clear();

    _window->draw(_background);    // Background
    drawTracks();                        // Tracks
    drawBullets();                        // Bullets
    _window->draw(_playerLine);    // Other lines and shapes
    if (_player.Visible())
        _window->draw(_player);

    _window->display();
}

void Game::drawTracks() 
{
    for (int i = 0; i < TOTAL_TRACKS; i++) _window->draw(_tracks[i]);
}

void Game::drawBullets() 
{
    for (auto& bullet : _bullets) _window->draw(bullet);
}