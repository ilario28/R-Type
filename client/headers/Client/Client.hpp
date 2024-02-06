/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Game
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "../Components/Components.hpp"
#include <SFML/Window/Event.hpp>
#include <functional>
#include "../../../game/headers/Game.hpp"
#include <asio.hpp>

class Button;
class ServerList;

#define PERCENTX(i) (i*windowSize.x / 100)
#define PERCENTY(i) (i*windowSize.y / 100)

enum state {
    MENU,
    SERVER_SELECTION,
    OPTIONS,
    LOBBY,
    GAME,
    OFFLINE,
    END
};

class UdpClient;

class Client {
public:
    Client();
    ~Client();
    void init();
    void loadState();
    void loadState(state newState);
    state getState() {return this->_state;};
    void lockGameEntities() {this->_gameEntitiesMutex.lock();};
    void unlockGameEntities() {this->_gameEntitiesMutex.unlock();};
    void setGameEntities(std::vector<std::pair<EntityList, std::pair<int, int>>> gameEntities) { this->_gameEntities = gameEntities;};
    void run();
    void playShotSound();
private:
    void handleEvents(sf::Event event);
    void clickHandler(sf::Event event);
    void keyHandler(sf::Event event);

    void update();
    void drawButtons();
    void render();

    std::vector<Button*> _buttons;
    ServerList *_serverList;

    void drawGameSpritesFromGameEntities(std::vector<std::pair<EntityList, std::pair<int, int>>> gameEntities);

    std::vector<std::pair<EntityList, std::pair<int, int>>> _gameEntities;
    std::vector<sf::Sprite> _gameSprites;
    int old_missile_nb;
    std::vector<std::thread> shootsThread;

    // OFFLINE features
    Rtype::Game *_game;
    void readGameInfo();

    // GAME features
    UdpClient* _game_server;
    void readServerInfo();
    std::thread _readServerInfoThread;
    std::mutex _gameEntitiesMutex;

    state _state;
    Background *_background;
    sf::Vector2f _movement;
    sf::Text upText;
    sf::Text downText;
    sf::Text leftText;
    sf::Text rightText;
    sf::Keyboard::Key upKey = sf::Keyboard::Unknown;
    sf::Keyboard::Key downKey = sf::Keyboard::Unknown;
    sf::Keyboard::Key leftKey = sf::Keyboard::Unknown;
    sf::Keyboard::Key rightKey = sf::Keyboard::Unknown;
    sf::Music music;
    sf::SoundBuffer shootBuffer;
    std::vector<sf::Sound> shoot;
    void loadMenu();
    void loadServerSelection();
    void loadGameOptions();
    void loadLobby();
    void loadGame();
    void loadOffline();
    void selectKey(const std::string& buttonName, sf::Keyboard::Key& key);
    void updateButtonLabel(const std::string& buttonName, sf::Keyboard::Key key);
    std::string keyToString(sf::Keyboard::Key key);

    //void loadEnd();
    sf::Vector2i _mousePosition;
    sf::RenderWindow *window;
};

class UdpClient {
    public:
        UdpClient(asio::io_service& io_service, const asio::ip::udp::endpoint& server_endpoint)
            : _socket(io_service), _server_endpoint(server_endpoint) {
        }

        void connect() {
            _socket.open(asio::ip::udp::v4());
            _socket.connect(_server_endpoint);
            sendCommand("connect");
        }

        void ready(Client *client) {
            sendCommand("ready");
            this->receive(client);
        }

        void receive(Client *client) {
            char data[1024];
            asio::error_code error;

            std::size_t bytes_received = _socket.receive(asio::buffer(data), 0, error);

            if (error && error != asio::error::message_size) {
                std::cerr << "Error receiving data: " << error.message() << std::endl;
            } else {
                std::string message(data, bytes_received);
                std::cout << "Received from server: " << message << std::endl;

                if (message.substr(0, 2) == "go" && client->getState() != GAME) client->loadState(GAME);
                if (message.substr(0, 4) == "data") {
                    client->lockGameEntities();
                    client->setGameEntities(this->getGameEntitiesViaMessage(message.substr(5)));
                    client->unlockGameEntities();
                }
            }
        }
        void sendCommand(const std::string& command) {
            std::vector<uint8_t> bytes(command.begin(), command.end());
            _socket.send(asio::buffer(bytes));
        }

    private:

        std::vector<std::pair<EntityList, std::pair<int, int>>> getGameEntitiesViaMessage(std::string message);

        asio::ip::udp::socket _socket;
        asio::ip::udp::endpoint _server_endpoint;
};
