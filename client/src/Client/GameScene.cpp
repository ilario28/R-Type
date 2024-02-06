/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Client
*/

 #include "../../headers/Client/Client.hpp"

static void set_menu_background(Background *background)
{
    background->addSprite("../client/assets/images/parralax/top_stars.png", sf::Vector2f(-1920, -1080), sf::Vector2f(2, 1), sf::Vector2f(3, 3));
    background->addSprite("../client/assets/images/parralax/mid_stars.png", sf::Vector2f(-1920, -1080), sf::Vector2f(4, 2), sf::Vector2f(3, 3));
    background->addSprite("../client/assets/images/parralax/bottom_stars.png", sf::Vector2f(-1920, -1080), sf::Vector2f(2, 1), sf::Vector2f(3, 3));
}

void Client::readServerInfo() {
    while (this->_state == GAME) {
        this->_game_server->receive(this);
    }
}

void Client::loadGame() { //load every item in the client screen
    set_menu_background(this->_background);
    this->music.openFromFile("../client/assets/sounds/music.wav");
    this->music.setVolume(50);
    this->music.setLoop(true);
    this->music.play();
    this->shootBuffer.loadFromFile("../client/assets/sounds/shoot.wav");
    this->_readServerInfoThread = std::thread([this]() { readServerInfo(); });
    while (!this->_gameEntities.size());   
}

void Client::readGameInfo() {
    while (this->_state == OFFLINE) {
        this->_gameEntities = this->_game->run();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Client::loadOffline() {
    this->_game = new Rtype::Game(2);
    set_menu_background(this->_background);
    this->music.openFromFile("../client/assets/sounds/music.wav");
    this->music.setVolume(50);
    this->music.setLoop(true);
    this->music.play();
    this->shootBuffer.loadFromFile("../client/assets/sounds/shoot.wav");
    this->_readServerInfoThread = std::thread([this]() { readGameInfo(); });
    while (!this->_gameEntities.size());
}