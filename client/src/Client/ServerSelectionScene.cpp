/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Client
*/

#include "../../headers/Client/Client.hpp"

void Client::loadServerSelection() { //load every item in the server selection screen
    //todo: start network thread
    //todo: get servers from network thread
    //todo: iterate through servers and create buttons for each one
    //Back button
    _buttons.push_back(new Button("Back", "../client/assets/images/buttons/default_button.png", sf::Vector2i(100, 700), sf::Vector2i(350, 100), [](Client *client) {
        client->loadState(MENU);
    }, this));
    _serverList->setShow(true);
}