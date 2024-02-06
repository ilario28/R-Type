/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Button
*/

#include "../../headers/Components/Button.hpp"

Button::Button(std::string name, std::string texturePath, sf::Vector2i position, sf::Vector2i size, std::function<void(Client *)> function, Client *client)
{
    _name = name;
    _texture = new sf::Texture();
    _texture->loadFromFile(texturePath);
    _sprite = new sf::Sprite(*_texture);
    _position = position;
    _size = size;
    _sprite->setPosition(_position.x, _position.y);
    _sprite->setScale(_size.x / _sprite->getLocalBounds().width, _size.y / _sprite->getLocalBounds().height);
    _isClicked = false;
    _function = function;
    _client = client;

    if (!font.loadFromFile("../client/assets/fonts/HIROMISAKE.ttf")) {
        // Handle font loading error
        std::cerr << "Couldn't load font for button " << this->_name << std::endl;
    }
    buttonText.setFont(font);
    buttonText.setCharacterSize(46);// Augmentez la taille de la police ici
    buttonText.setFillColor(sf::Color::White);
    buttonText.setStyle(sf::Text::Bold);

    sf::FloatRect buttonBounds = _sprite->getGlobalBounds();
    sf::FloatRect textBounds = buttonText.getGlobalBounds();

    // Calculez la position x et y pour centrer le texte
    float xPos = buttonBounds.left + (buttonBounds.width + textBounds.width) / 4;
    float yPos = buttonBounds.top + (buttonBounds.height + textBounds.height) / 4;

    buttonText.setPosition(xPos, yPos);
    buttonText.setString(_name);

    }

void Button::draw(sf::RenderWindow *window) const
{
    window->draw(*_sprite);
    window->draw(buttonText);
}

bool Button::isMouseOver(sf::Vector2i mousePosition) const
{
    bool result = false;
    sf::FloatRect buttonBounds = _sprite->getGlobalBounds();
    result = buttonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    return (result);
}

void Button::click() const
{
    _function(_client);
}

Button::~Button()
{
    delete _texture;
    delete _sprite;
}
