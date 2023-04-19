#include <SFML/Graphics.hpp>
#include "game.hpp"

using namespace sf;

int main() 
{
    RenderWindow window(VideoMode(800, 800), "Doodle Mania");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    Image icon;
    icon.loadFromFile("images/icon.jpg");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Game partie(window);
    partie.play();
}