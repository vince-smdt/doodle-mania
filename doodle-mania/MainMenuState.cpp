#include "Game.h"
#include "GameState.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(std::shared_ptr<GameData> data) : _data(data) {}

void MainMenuState::Init()
{
    // Initialize play button
    _playButton.SetColor(sf::Color::White);
    _playButton.SetFont(_data->assets.GetFont("font_raleway"));
    _playButton.SetFontColor(sf::Color::Black);
    _playButton.SetFontSize(50);
    _playButton.SetOutlineColor(sf::Color::Black);
    _playButton.SetOutlineThickness(2);
    _playButton.SetPosition(sf::Vector2f(_data->window.getSize().x / 2, _data->window.getSize().y / 2));
    _playButton.SetSize(sf::Vector2f(400, 100));
    _playButton.SetText("Play");

    // Initialize background
    _background.setFillColor(sf::Color::White);
    _background.setSize(sf::Vector2f(_data->window.getSize().x, _data->window.getSize().y));
    _background.setPosition(sf::Vector2f(0, 0));
}

void MainMenuState::HandleInput(sf::Event event)
{
    if (event.type == sf::Event::Closed)
    {
        _data->window.close();
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (_playButton.MouseHovering(_data->window))
        {
            _data->machine.AddState(StateRef(new GameState(_data)));
        }
    }
}

void MainMenuState::Update(float delta) {}

void MainMenuState::Draw(float delta) const
{
    _data->window.clear();

    _data->window.draw(_background);
    _playButton.Draw(_data->window);

    _data->window.display();
}