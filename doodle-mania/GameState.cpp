#include "Game.h"
#include "GameState.h"
#include "Level.h"

GameState::GameState(std::shared_ptr<GameData> data)
    : _data(data)
{
    Init();
}

void GameState::Init()
{
    _level = LevelGenerator::GenerateFromFile("levels/testcopy.txt");

    _playerTrackPos = _level->GetNumberOfTracks() / 2;

    // Initialize tracks
    _tracks.resize(_level->GetNumberOfTracks());
    for (unsigned int i = 0; i < _level->GetNumberOfTracks(); i++)
    {
        _tracks[i].setSize(sf::Vector2f(4, _data->window.getSize().y));
        _tracks[i].setOrigin(sf::Vector2f(2, _tracks[i].getSize().y));
        _tracks[i].setPosition(sf::Vector2f(((_data->window.getSize().x / 2) - (floor(_tracks.size() / 2) * TRACKS_DIST_APART)) + (i * TRACKS_DIST_APART), _tracks[i].getSize().y));
        _tracks[i].setFillColor(sf::Color(100, 100, 100));
    }

    // Initialize background
    _background.setFillColor(sf::Color::White);
    _background.setSize(sf::Vector2f(_data->window.getSize().x, _data->window.getSize().y));
    _background.setPosition(sf::Vector2f(0, 0));

    // Initialize additional shapes
    _playerLine.setFillColor(sf::Color(100, 100, 100));
    _playerLine.setSize(sf::Vector2f(TRACKS_DIST_APART * (_tracks.size() - 1), 4));
    _playerLine.setOrigin(sf::Vector2f(_playerLine.getSize().x / 2, _playerLine.getSize().y / 2));
    _playerLine.setPosition(sf::Vector2f(_data->window.getSize().x / 2, _data->window.getSize().y / 1.2));

    // Initialize player position
    _player.InstantlyMoveTo(_tracks[_playerTrackPos].getPosition().x, _playerLine.getPosition().y);

    // Start music and restart clocks
    _level->LoadMusic("music/Boogie Vice - Enter The Rave.wav", 50);
    _level->PlayMusic();
    _bulletSpawnClock.restart();
}

void GameState::HandleInput(sf::Event event)
{
    if (event.type == sf::Event::Closed)
    {
        _data->window.close();
    }
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Left:
            {
                if (_playerTrackPos > 0)
                {
                    _playerTrackPos--;
                    _player.MoveTo(_tracks[_playerTrackPos].getPosition().x, _player.getPosition().y);
                }
                break;
            }
            case sf::Keyboard::Right:
            {
                if (_playerTrackPos < _level->GetNumberOfTracks() - 1)
                {
                    _playerTrackPos++;
                    _player.MoveTo(_tracks[_playerTrackPos].getPosition().x, _player.getPosition().y);
                }
                break;
            }
        }
    }
}

void GameState::Update(float delta)
{
    // Update player states
    _player.UpdateFlashState();
    _player.UpdateMoveState();

    // Handle bullets
    MoveBullets();
    DeleteOffscreenBullets();
    SpawnBullets();

    // Check if player/bullet collision
    if (PlayerCollidesWithBullet() && !_player.IsHit())
        _player.Hit();

    _player.rotate(1);
    Draw(0.0f);
}

void GameState::Draw(float delta) const
{
    _data->window.clear();

    _data->window.draw(_background);                             // Background
    for (auto& track : _tracks) _data->window.draw(track);       // Tracks
    for (auto& bullet : _bullets) _data->window.draw(bullet);    // Bullets
    _data->window.draw(_playerLine);                             // Other lines and shapes
    if (_player.Visible()) _data->window.draw(_player);          // Player

    _data->window.display();
}

void GameState::MoveBullets()
{
    for (auto& bullet : _bullets)
    {
        bullet.move(0.0f, bullet.GetSpeed());
    }
}

void GameState::SpawnBullets()
{
    while (!_level->GetBulletSpawns().empty() && _level->GetBulletSpawns().front().GetSpawnTime() <= _bulletSpawnClock.getElapsedTime().asMilliseconds())
    {
        int trackNum = _level->GetBulletSpawns().front().GetTrack();
        float posX = _tracks[trackNum].getPosition().x;
        float speed = _level->GetBulletSpawns().front().GetSpeed();
        sf::Color bColor = _level->GetBulletSpawns().front().GetColor();

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

void GameState::DeleteOffscreenBullets()
{
    while (!_bullets.empty() && _bullets.front().getPosition().y > _data->window.getSize().y + _bullets.front().getRadius() * 2)
    {
        _bullets.erase(_bullets.begin());
    }
}
