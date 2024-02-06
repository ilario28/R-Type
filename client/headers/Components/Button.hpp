/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Button
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "../Client/Client.hpp"

class Client;

class Button {
    public:
        Button(std::string name, std::string texturePath, sf::Vector2i position, sf::Vector2i size, std::function<void(Client *client)> function, Client *client);
        bool isMouseOver(sf::Vector2i mousePosition) const;
        void draw(sf::RenderWindow *window) const;
        void click() const;
        std::string getName() const {return _name;};
        ~Button();
        bool operator<(const Button &button) const {
            return _name < button._name;
        };

    private:
        std::string _name;
        Client *_client;
        sf::Texture *_texture;
        sf::Sprite *_sprite;
        sf::Vector2i _position;
        sf::Vector2i _size;
        bool _isClicked;
        std::function<void(Client *client)> _function;
        sf::Text buttonText;
        sf::Font font;
};
