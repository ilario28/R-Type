/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Game
*/

#include "../headers/Game.hpp"
#include "../headers/Systems.hpp"

Rtype::Game::Game(int playerNumber)
{
    _playerNumber = playerNumber;
    _status = Rtype::GameStatus::Game;
    this->_engine = new Engine::GameEngine();
    Rtype::Systems::buildGameSystems(_engine->getSystems());
    for (int i = 0; i != _playerNumber; i++)
        EntityFactory::buildSpaceshipEntity(this->_engine->getEntities(), this->_engine->getEntitySignatures(), i + 1, std::make_pair(100, i * 200 + 200));
    this->ennemyThread = std::thread([this]() { ennemiesIA(); });
}

static std::pair<int, int> rand_spawn_location()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribX(500, 1700);
    std::uniform_int_distribution<int> distribY(0, 950);

    int randomX = distribX(gen);
    int randomY = distribY(gen);
    return std::make_pair(randomX, randomY);
}

std::map<int, sf::Clock> Rtype::Game::cleanUselessClocks(std::vector<Engine::Entity> entities, std::vector<Engine::Signature> entitySignatures, std::map<int, sf::Clock> shootClocks)
{
    std::bitset<MAX_COMPONENTS> enemySignature(EntityType | VelocityComponent | DrawableComponent | SizeComponent | ControllerComponent | PositionComponent);
    auto it = shootClocks.begin();

    while (it != shootClocks.end()) {
        bool found = false;

        for (size_t i = 0; i < entities.size(); ++i) {
            if ((entitySignatures[i].getBits() & enemySignature) == enemySignature) {
                if (Engine::Component::FindComponentByType("Controller", &entities[i])->getData<int>() == it->first) {
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            it = shootClocks.erase(it);
        } else {
            ++it;
        }
    }

    return shootClocks;
}

void Rtype::Game::ennemiesIA()
{
    int ennemies_max_id = 100;
    std::map<int, sf::Clock> shootClocks;
    sf::Clock cleanupClock;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    while (this->_status == Rtype::GameStatus::Game) {
        if (this->spawnClock.getElapsedTime().asMilliseconds() > 3000) {
            EntityFactory::buildEnnemyEntity(this->_engine->getEntities(), this->_engine->getEntitySignatures(), ennemies_max_id, rand_spawn_location());
            shootClocks[ennemies_max_id] = sf::Clock();
            ennemies_max_id++;
            if (ennemies_max_id > 10000) ennemies_max_id = 100;
            this->spawnClock.restart();
        }
        for (auto it = shootClocks.begin(); it != shootClocks.end(); it++) {
            int entityID = it->first;
            sf::Clock& enemyClock = it->second;

            if (enemyClock.getElapsedTime().asMilliseconds() > 500) {
                this->addEvent(SHOOT, LEFT, entityID);
                enemyClock.restart();
            }
        }
        if (cleanupClock.getElapsedTime().asMilliseconds() > 5000) {
            mutex.lock();
            shootClocks = cleanUselessClocks(*(this->_engine->getEntities()), *(this->_engine->getEntitySignatures()), shootClocks);
            mutex.unlock();
            cleanupClock.restart();
        }
    }
}

std::vector<std::pair<EntityList, std::pair<int, int>>> Rtype::Game::run()
{
    if (this->_status == Rtype::GameStatus::Game) {
        mutex.lock();
        this->_engine->run();
        mutex.unlock();
        return (this->getDrawableEntities());
    } else {
        return std::vector<std::pair<EntityList, std::pair<int, int>>>();
    }
}

std::vector<std::pair<EntityList, std::pair<int, int>>> Rtype::Game::getDrawableEntities()
{
    Rtype::GameStatus tempStatus = Rtype::GameStatus::End;
    std::vector<Engine::Signature> *entitySignatures = this->_engine->getEntitySignatures();
    std::vector<Engine::Entity> *entities = this->_engine->getEntities();
    Engine::Signature DrawableEntitySignature(PositionComponent | DrawableComponent | EntityType);
    std::vector<std::pair<EntityList, std::pair<int, int>>> result;

    for (int i = 0; entities->size() != i; i++) {
        if ((DrawableEntitySignature.getBits() | entitySignatures->at(i).getBits()) == entitySignatures->at(i).getBits())
            if (tempStatus == Rtype::GameStatus::End && Engine::Component::FindComponentByType("EntityType", &entities->at(i))->getData<EntityList>() == SPACESHIP)
                tempStatus = Rtype::GameStatus::Game;
            result.push_back(std::make_pair(
                Engine::Component::FindComponentByType("EntityType", &entities->at(i))->getData<EntityList>(),
                Engine::Component::FindComponentByType("Position", &entities->at(i))->getData<std::pair<int, int>>()
            ));
    }
    this->_status = tempStatus;
    return result;
}

Rtype::Game::~Game() {
    delete _engine;
}