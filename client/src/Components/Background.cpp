/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Background.cpp
*/

#include "../../headers/Components/Background.hpp"

Background::Background()
{
    clock = new sf::Clock();
}

void Background::addSprite(std::string texturePath, sf::Vector2f position, sf::Vector2f speed, sf::Vector2f scale)
{
    backgroundSprite sprite;
    sprite.texture = new sf::Texture();
    sprite.texture->loadFromFile(texturePath);
    sprite.sfSprite = new sf::Sprite(*sprite.texture);
    sprite.position = position;
    sprite.sfSprite->setPosition(sprite.position);
    sprite.speed = speed;
    sprite.scale = scale;
    spriteObjects.push_back(sprite);
}

void Background::draw(sf::RenderWindow *window, sf::Vector2f movement)
{
    int time = clock->getElapsedTime().asMilliseconds();
    clock->restart();
    sf::Vector2f scale;
    sf::Vector2u windowSize = window->getSize();
    for (auto object : spriteObjects) {
        scale.x = (float)(windowSize.x) / (object.texture->getSize().x) * (float)(object.scale.x);
        scale.y = (float)(windowSize.y) / (object.texture->getSize().y) * (float)(object.scale.y);
        object.sfSprite->setScale(scale);
        object.sfSprite->move(-object.speed.x * movement.x * time/10, object.speed.y * movement.y * time/10);
        update();

        window->draw(*object.sfSprite);
    }
}

void Background::update()
{
    for (auto i : spriteObjects) {
        if (i.sfSprite->getPosition().x < -3840) {
            i.sfSprite->setPosition(i.sfSprite->getPosition().x + 1920, i.sfSprite->getPosition().y);
        }
        if (i.sfSprite->getPosition().x > 0) {
            i.sfSprite->setPosition(i.sfSprite->getPosition().x - 1920, i.sfSprite->getPosition().y);
        }
        if (i.sfSprite->getPosition().y < -2160) {
            i.sfSprite->setPosition(i.sfSprite->getPosition().x, i.sfSprite->getPosition().y + 1080);
        }
        if (i.sfSprite->getPosition().y > 0) {
            i.sfSprite->setPosition(i.sfSprite->getPosition().x, i.sfSprite->getPosition().y - 1080);
        }
    }
}

void Background::clear()
{
    while(spriteObjects.size() > 0) {
        spriteObjects.erase(spriteObjects.begin());
    }
}

Background::~Background()
{
}