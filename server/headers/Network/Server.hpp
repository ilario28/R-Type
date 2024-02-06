/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Server
*/

#include <iostream>
#include <vector>
#include <thread>
#include <asio.hpp>
#include "../../../game/headers/Game.hpp"

constexpr int max_clients = 4;

class UdpServer {
public:
    UdpServer(asio::io_service& io_service, int port)
        : _socket(io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)) { _isInGame = false; }

    void start();

    ~UdpServer() {
        _receive_thread.join();
        _process_thread.join();
    }

private:
    struct ClientInfo {
        bool ready;
        asio::ip::udp::endpoint endpoint;
    };

    void ReceiveData();
    void addActionGameToQueue(std::string message, int playerID);
    void ProcessData();

    std::vector<uint8_t> parseEntitiesToBytes(std::vector<std::pair<EntityList, std::pair<int, int>>> entities);

    asio::ip::udp::socket _socket;
    std::vector<ClientInfo> _clients;
    std::thread _receive_thread;
    std::thread _process_thread;
    Rtype::Game *game;
    std::vector<uint8_t> _entitiesPacket;
    bool _isInGame;
};
