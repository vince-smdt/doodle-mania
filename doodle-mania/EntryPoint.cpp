#include <SFML/Graphics.hpp>
#include "GameState.h"

int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Doodle Mania");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Image icon;
    icon.loadFromFile("images/icon.jpg");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    GameState game(window);
    game.Play();
}