#include "EditorState.h"
#include "Game.h"

EditorState::EditorState(std::shared_ptr<GameData> data) : _data(data) {}

void EditorState::Init()
{
    _backButton.SetColor(sf::Color::White);
    _backButton.SetFont(_data->assets.GetFont("font_raleway"));
    _backButton.SetFontColor(sf::Color::Black);
    _backButton.SetFontSize(16);
    _backButton.SetOutlineColor(sf::Color::Black);
    _backButton.SetOutlineThickness(2);
    _backButton.SetPosition(sf::Vector2f(75, 25));
    _backButton.SetSize(sf::Vector2f(100, 25));
    _backButton.SetText("Back");
}

void EditorState::HandleInput(sf::Event event)
{
    if (event.type == sf::Event::Closed)
    {
        _data->window.close();
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        if (_backButton.MouseHovering(_data->window))
        {
            _data->machine.RemoveState();
        }
    }
}

void EditorState::Update(float delta)
{

}

void EditorState::Draw(float delta) const
{
    _data->window.clear(sf::Color::White);

    _backButton.Draw(_data->window);

    _data->window.display();
}
