/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** ServerList.hpp
*/

#pragma once
#include <string>
#include <vector>
#include "Button.hpp"
#include "../Client/Client.hpp"
#include <SFML/Graphics.hpp>

struct Server_t {
    std::string name;
    std::string ip;
    int port;
    std::string status;
    int nbPlayers;
    int maxPlayers;
};

class Client;
class Button;

class ServerList
{
public:
    ServerList(Client *clientptr, sf::RenderWindow *window /*To do: network thread data pointer*/);
    ~ServerList();
    void setShow(bool show) {_show = show;};
    bool getShow() {return _show;};
    void draw();
    void update();
    bool clickCheck(sf::Event event);
    void scroll(sf::Event event);
    std::vector<Button*> _buttons;
private:
    bool _show;
    std::vector<Server_t> _servers;
    Client *_clientptr;
    sf::RenderWindow *_window;
    sf::Clock _updateTimer;
    int _scroll;
};
