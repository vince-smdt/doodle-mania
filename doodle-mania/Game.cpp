#include "Game.h"

Game::Game()
{
    _data = std::make_shared<GameData>();

    _data->window.create(sf::VideoMode(800, 800), "Doodle Mania", sf::Style::Close | sf::Style::Titlebar);

    _data->machine.AddState(StateRef(new GameState(_data)));

    srand(time(0));
}

void Game::Run()
{
    float newTime, frameTime, interpolation;
    float currentTime = _clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;
    sf::Event event;

    while (_data->window.isOpen())
    {
        _data->machine.ProcessStateChanges();

        newTime = _clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if (frameTime > 0.25f)
            frameTime = 0.25f;

        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= dt)
        {
            while (_data->window.pollEvent(event))
            {
                _data->machine.GetActiveState()->HandleInput(event);
            }
            _data->machine.GetActiveState()->Update(dt);
            accumulator -= dt;
        }

        interpolation = accumulator / dt;
        _data->machine.GetActiveState()->Draw(interpolation);
    }
}
