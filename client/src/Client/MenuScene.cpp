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

static void set_menu_buttons(std::vector<Button*> *button, Client *client, sf::RenderWindow *window)
{
    std::function<void(Client*)> Play = [](Client *client) {client->loadState(LOBBY);};
    std::function<void(Client*)> Offline = [](Client *client) {client->loadState(OFFLINE);};
    std::function<void(Client*)> Quit = [window](Client *client) {window->close();};
    std::function<void(Client*)>Options = [](Client *client) {client->loadState(OPTIONS);};
    button->push_back(new Button("Play", "../client/assets/images/buttons/default_button.png", sf::Vector2i(850, 150), sf::Vector2i(350, 100), Play, client));
    button->push_back(new Button("Offline", "../client/assets/images/buttons/default_button.png", sf::Vector2i(850, 220), sf::Vector2i(350, 100), Offline, client));
    button->push_back(new Button("Quit", "../client/assets/images/buttons/default_button.png", sf::Vector2i(850, 360), sf::Vector2i(350, 100), Quit, client));

    button->push_back(new Button("Options", "../client/assets/images/buttons/default_button.png", sf::Vector2i(850, 290), sf::Vector2i(350, 100), Options, client));
}

void Client::loadMenu() {  //load every item in the menu screen
    _serverList->setShow(false);
    //kill network thread if it exists
    //Button functions
    set_menu_buttons(&_buttons, this, window);
    set_menu_background(_background);
}
