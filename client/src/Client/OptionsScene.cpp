/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Client
*/

#include "../../headers/Client/Client.hpp"

void Client::loadGameOptions() {
    std::function<void(Client*)> SelectUpControl = [this](Client* client) {
        selectKey("Up", upKey);
    };

    std::function<void(Client*)> SelectDownControl = [this](Client* client) {
        selectKey("Down", downKey);
    };

    std::function<void(Client*)> SelectLeftControl = [this](Client* client) {
        selectKey("Left", leftKey);
    };

    std::function<void(Client*)> SelectRightControl = [this](Client* client) {
        selectKey("Right", rightKey);
    };
    _background->addSprite("../client/assets/images/options/Fond_options.jpg", sf::Vector2f(0,0), sf::Vector2f(0, 0), sf::Vector2f(1, 1));

    _buttons.push_back(new Button("Up", "../client/assets/images/buttons/default_button.png", sf::Vector2i(850, 150), sf::Vector2i(350, 100), SelectUpControl, this));
    _buttons.push_back(new Button("Down", "../client/assets/images/buttons/default_button.png", sf::Vector2i(850, 225), sf::Vector2i(350, 100), SelectDownControl, this));
    _buttons.push_back(new Button("Left", "../client/assets/images/buttons/default_button.png", sf::Vector2i(850, 300), sf::Vector2i(350, 100), SelectLeftControl, this));
    _buttons.push_back(new Button("Right", "../client/assets/images/buttons/default_button.png", sf::Vector2i(850, 375), sf::Vector2i(350, 100), SelectRightControl, this));
    _buttons.push_back(new Button("Back", "../client/assets/images/buttons/default_button.png", sf::Vector2i(100, 700), sf::Vector2i(350, 100), [](Client *client) {
        client->loadState(MENU);
    }, this));
}

void Client::selectKey(const std::string& buttonName, sf::Keyboard::Key& key) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Select Key", sf::Style::None);
    window.setKeyRepeatEnabled(false);
    window.clear(sf::Color(0, 0, 0, 0));

    bool selectingKey = true;

    sf::Font font;
    font.loadFromFile("../client/assets/fonts/HIROMISAKE.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Select a Key");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(960, 540);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                key = event.key.code;
                selectingKey = false;
                window.close();
            }
        }

        window.clear();
        window.draw(text);
        window.display();

        if (!selectingKey) {
            break;
        }
    }
}


void Client::updateButtonLabel(const std::string& buttonName, sf::Keyboard::Key key) {
    std::cout << "Button '" << buttonName << "' assigned to key: " << key << std::endl;
}
