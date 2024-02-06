/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Client
*/

#include "../../headers/Client/Client.hpp"

void Client::loadLobby() { //load every item in the lobby screen
    asio::io_service io_service;
    asio::ip::udp::endpoint server_endpoint(asio::ip::address::from_string("127.0.0.1"), 41220);
    std::function<void(Client*)> Ready = [](Client *client) {
        client->_game_server->ready(client);
    };
    this->_game_server = new UdpClient(io_service, server_endpoint);
    _game_server->connect();
    this->_buttons.push_back(new Button("Ready", "../client/assets/images/buttons/default_button.png", sf::Vector2i(850, 150), sf::Vector2i(350, 100), Ready, this));
}