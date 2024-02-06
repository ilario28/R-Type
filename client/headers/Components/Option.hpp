/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Option
*/

#pragma once
#include  "../Client/Client.hpp"

#define OPTIONS_PATH "client/assets/options.json"

struct backgroundSprite {
    sf::Sprite *sprite;
    sf::Vector2f position;
    sf::Texture *backgroundTexture;

};

typedef struct commands {
    int up;
    int down;
    int left;
    int right;
    char *to_change;
    sf::Text upText;
    sf::Text downText;
    sf::Text leftText;
    sf::Text rightText;
} command_t;

class Option {
    public:
        Option();
    void addSprite(std::string texturePath, sf::Vector2f position, sf::Vector2f speed);
    void selectKey(const std::string& buttonName, sf::Keyboard::Key& key);

        ~Option();

    protected:
    private:
};