#pragma once
#include<SFML/Graphics.hpp>

class Character
{
    public:
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f velocity;
        sf::Vector2f position;
        float speed;
        bool isAlive;

        Character()
        {
            // 设置角色为一个纯白色的矩形
            isAlive = true;
            sf::Image image;
            image.create(50, 50, sf::Color::White);
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            position = sf::Vector2f(0, 0);
            sprite.setPosition(position);
            speed = 10;
            velocity = sf::Vector2f(0, 0);
            sprite.setOrigin(25, 25);
        }

        void handleInput()
        {
            velocity = sf::Vector2f(0, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                velocity.y -= speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                velocity.y += speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                velocity.x -= speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                velocity.x += speed;
        }
        void update(sf::RenderWindow &window)
        {
            position += velocity;
            sprite.setPosition(position);
            window.draw(sprite);
        }
};