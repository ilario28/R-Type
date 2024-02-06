/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** ServerList.cpp
*/

#include "../../headers/Components/ServerList.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
using namespace nlohmann;

static json getTestServers()
{
    std::ifstream i("../client/assets/test/servers.json");
    json servers = json::parse(i);
    i.close();
    return servers;
}

ServerList::ServerList(Client *clientptr, sf::RenderWindow *window /*To do: network thread data pointer*/)
    : _clientptr(clientptr), _window(window)
{
    _updateTimer.restart();

}

void ServerList::draw()
{
    // draw serverList container
    if (!_show) return;
    for (auto &button : _buttons) {
        button->draw(_window);
    }
}

void ServerList::update()
{
    // To do: get information from network thread
    int time = _updateTimer.getElapsedTime().asSeconds();
    if (time < 5) return;
    if (!_show) return;
    _updateTimer.restart();
    json servers = getTestServers(); // To do: get servers from network thread
    while(_servers.size() > 0) {
        _servers.erase(_servers.begin());
    }
    for (auto &server : servers) {
        Server_t newServer;
        newServer.name = server["name"];
        newServer.ip = server["ip"];
        newServer.port = server["port"];
        newServer.status = server["status"];
        newServer.nbPlayers = server["players"];
        newServer.maxPlayers = server["maxplayers"];
        _servers.push_back(newServer);
    }
    while(_buttons.size() > 0) {
        _buttons.erase(_buttons.begin());
    }
    int i = 1;
    for (auto &server : _servers) {
        // create buttons
        _buttons.push_back(new Button(server.name, "../client/assets/images/buttons/default_button.png", sf::Vector2i(_window->getSize().x/2, 100*i), sf::Vector2i(350, 100), [](Client *client) {
            client->loadState(LOBBY);
        }, _clientptr));
        i++;
    }
}

bool ServerList::clickCheck(sf::Event event)
{
    bool buttonClicked = false;
    sf::Vector2i _mousePosition = sf::Mouse::getPosition(*_window);
    if(!_show) return false;
    if(event.mouseButton.button == sf::Mouse::Left) {
        for(auto button : _buttons) {
            if (button->isMouseOver(_mousePosition)) {
                button->click();
                buttonClicked = true;
                break;
            }
        }
    }
    return buttonClicked;
}

ServerList::~ServerList()
{
}