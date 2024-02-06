/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Server
*/

#include "../../headers/Network/Server.hpp"

void UdpServer::start() {
    this->_receive_thread = std::thread([this]() { ReceiveData(); });
    this->_process_thread = std::thread([this]() { ProcessData(); });
}

void UdpServer::ProcessData()
{
    while (true) {
        if (this->_clients.size() && std::all_of(this->_clients.begin(), this->_clients.end(), [](const ClientInfo& client) { return client.ready; })) {
            for (const ClientInfo& client : this->_clients) {
                this->_socket.send_to(asio::buffer("go"), client.endpoint);
                this->_isInGame = true;
                this->game = new Rtype::Game(this->_clients.size());
            }
            for (ClientInfo& client : this->_clients) {
                client.ready = false;
            }
        }
        while (this->_isInGame) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            this->_entitiesPacket = this->parseEntitiesToBytes(this->game->run());
            // std::cout << "send this: " << this->_entitiesPacket << std::endl;
            for (const ClientInfo& client : this->_clients)
                this->_socket.send_to(asio::buffer(this->_entitiesPacket), client.endpoint);
        }
    }
}
// data-EntityListName-X-Y_EntityListName-X-Y_EntityListName-X-Y...
std::vector<uint8_t> UdpServer::parseEntitiesToBytes(std::vector<std::pair<EntityList, std::pair<int, int>>> entities) {
    std::string stringified;

    for (const auto &entity : entities) {
        stringified += std::to_string(entity.first) + '.' +
                        std::to_string(entity.second.first) + '.' +
                        std::to_string(entity.second.second) + '_';
    }
    if (!stringified.empty()) stringified.pop_back();

    stringified = "data-" + stringified;

    std::vector<uint8_t> bytes(stringified.begin(), stringified.end());
    return bytes;
}

void UdpServer::addActionGameToQueue(std::string message, int playerId)
{
    std::istringstream ss(message);
    std::string entityInfo;
    int action[2];

    for (int i = 0; i != 2; i++) {
        getline(ss, entityInfo, '_');
        action[i] = std::atoi(entityInfo.c_str());
    }

    this->game->addEvent(action[0], action[1], playerId);
}

void UdpServer::ReceiveData()
{
    char data[1024];
    asio::error_code error;

    while (true) {
        asio::ip::udp::endpoint remote_endpoint;
        std::size_t bytes_received = this->_socket.receive_from(asio::buffer(data), remote_endpoint, 0, error);
        if (error && error != asio::error::message_size) {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
            break;
        }
        std::string message(data, bytes_received);
        std::cout << "Received from " << remote_endpoint.address().to_string() << ": " << message << std::endl;
        if (!this->_isInGame) {
            if (message == "connect") {
                if (this->_clients.size() < max_clients) {
                    ClientInfo newClient;
                    newClient.ready = false;
                    newClient.endpoint = remote_endpoint;
                    this->_clients.push_back(newClient);
                }
            }
            else if (message == "ready") {
                for (ClientInfo& client : this->_clients) {
                    if (client.endpoint == remote_endpoint) {
                        client.ready = true;
                        break;
                    }
                }
            }
        }
        if (message.substr(0, 6) == "action") {
            for (int i = 0; i != this->_clients.size(); i++)
                if (this->_clients.at(i).endpoint == remote_endpoint)
                    this->addActionGameToQueue(message.substr(7), i + 1);
        }
        if (message == "disconnect") {
            for (auto it = this->_clients.begin(); it != this->_clients.end(); ++it) {
                if (it->endpoint == remote_endpoint) {
                    this->_clients.erase(it);
                    break;
                }
            }
        }
    }
}

