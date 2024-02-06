/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** main
*/

#include "../headers/Network/Server.hpp"

int main() {
    try {
        asio::io_service io_service;
        UdpServer server(io_service, 41220);
        server.start();

        io_service.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}