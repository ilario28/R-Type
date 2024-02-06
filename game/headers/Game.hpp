/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Game
*/

#pragma once

#include <iostream>

#include "EntityFactory.hpp"
#include "Systems.hpp"
#include <GameEngine>
#include <SFML/System/Clock.hpp>
#include <thread>
#include <random>
#include <mutex>
#include <map>

namespace Rtype {
    enum class GameStatus { Lobby, Game, End };

    class Game {
        public:
            Game(int playerNumber);
            std::vector<std::pair<EntityList, std::pair<int, int>>> run();
            std::vector<std::pair<EntityList, std::pair<int, int>>> getDrawableEntities();
            void addEvent(int type, int value, int EntityId) {this->_engine->getEvents()->push_back(Engine::Event(type, value, EntityId));};
            ~Game();
        private:
            void ennemiesIA();
            std::map<int, sf::Clock> cleanUselessClocks(std::vector<Engine::Entity> entities, std::vector<Engine::Signature> entitySignatures, std::map<int, sf::Clock> shootClocks);

            int _playerNumber;
            Rtype::GameStatus _status;
            Engine::GameEngine *_engine;
            sf::Clock spawnClock;
            std::thread ennemyThread;
            std::mutex mutex;
    };
}
