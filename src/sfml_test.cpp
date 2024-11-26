#include<SFML/Graphics.hpp>
#include<iostream>
#include"res/character.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/wqy/wqy-microhei.ttc"))
    {
        std::cout << "load font failed" << std::endl;
        return -1;
    }
    text.setFont(font);
    text.setString("click at");
    Character player;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player.handleInput();
        // 检测鼠标点击
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            text.setString("click at " + std::to_string(mousePos.x) + " " + std::to_string(mousePos.y));
            text.setPosition(mousePos.x, mousePos.y);
        }
        window.clear();
        window.draw(text);
        player.update(window);
        window.display();
    }
    return 0;
}