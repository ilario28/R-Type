/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Background.hpp
*/

#ifndef Background_HPP
#define Background_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

struct backgroundSprite {
    sf::Sprite *sfSprite;
    sf::Texture *texture;
    sf::Vector2f position;
    sf::Vector2f speed;
    sf::Vector2f scale;
};

class Background {
public:
    int _speed;
    Background();
    void addSprite(std::string texturePath, sf::Vector2f position, sf::Vector2f speed, sf::Vector2f scale = sf::Vector2f(1, 1));
    void draw(sf::RenderWindow *window, sf::Vector2f movement);
    ~Background();
    void update();
    void clear();

private:
    std::vector<backgroundSprite> spriteObjects;
    sf::Clock *clock;
};

#endif // Background_HPP