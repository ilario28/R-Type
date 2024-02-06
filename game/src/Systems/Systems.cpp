/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Systems
*/

#include "../../headers/Systems.hpp"
#include "../../headers/EntityFactory.hpp"

void Rtype::Systems::buildGameSystems(std::vector<Engine::System> *systems)
{
    systems->push_back(std::make_pair(Rtype::Systems::moveEntityByController, Engine::Signature(std::bitset<MAX_COMPONENTS>(ControllerComponent | PositionComponent | VelocityComponent))));
    systems->push_back(std::make_pair(Rtype::Systems::moveEntityByInertia, Engine::Signature(std::bitset<MAX_COMPONENTS>(ObjectComponent | PositionComponent | VelocityComponent))));
    systems->push_back(std::make_pair(Rtype::Systems::shootMissile, Engine::Signature(std::bitset<MAX_COMPONENTS>(ControllerComponent | PositionComponent))));
    systems->push_back(std::make_pair(Rtype::Systems::objectHit, Engine::Signature(std::bitset<MAX_COMPONENTS>(ObjectComponent | PositionComponent | SizeComponent))));
}

void Rtype::Systems::moveEntityByController(std::vector<Engine::Entity> *entityArr, int entityIndex, Engine::eventQueue *events, std::vector<Engine::Signature> *entitySignature)
{
    Engine::Entity *entity = &entityArr->at(entityIndex);
    Engine::Component *controllercmp = Engine::Component::FindComponentByType("Controller", entity);
    if(controllercmp->getType() == std::string("err")) {
        std::cerr << "shockbar de bz tes signatures sont rincées" << std::endl;
        return;
    }
    Engine::Component *positioncmp = Engine::Component::FindComponentByType("Position", entity);
    if(positioncmp->getType() == std::string("err")) {
        std::cerr << "shockbar de bz tes signatures sont rincées" << std::endl;
        return;
    }
    Engine::Component *velocitycmp = Engine::Component::FindComponentByType("Velocity", entity);
    if(velocitycmp->getType() == std::string("err")) {
        std::cerr << "shockbar de bz tes signatures sont rincées" << std::endl;
        return;
    }
    int controllerId = controllercmp->getData<int>();
    std::pair<int, int> position = positioncmp->getData<std::pair<int, int>>();
    int velocity = velocitycmp->getData<int>();
    Engine::eventQueue::iterator it = events->begin();
    while(it != events->end()) {
        if(it->getType() == MOVE && it->getOwner() == controllerId) {
            switch (it->getValue())
            {
            case UP:
                if (position.second > 0) {
                    position.second -= velocity;
                    positioncmp->setData<std::pair<int, int>>(position);
                }
                break;
            case DOWN:
                if (position.second < 950) {
                    position.second += velocity;
                    positioncmp->setData<std::pair<int, int>>(position);
                }
                break;
            case LEFT:
                if (position.first > 0) {
                    position.first -= velocity;
                    positioncmp->setData<std::pair<int, int>>(position);
                }
                break;
            case RIGHT:
                if (position.first < 500) {
                    position.first += velocity;
                    positioncmp->setData<std::pair<int, int>>(position);
                }
                break;
            }
            it = events->erase(it);
        } else ++it;
    }
}

void Rtype::Systems::moveEntityByInertia(std::vector<Engine::Entity> *entityArr, int entityIndex, Engine::eventQueue *events, std::vector<Engine::Signature> *entitiesSignature)
{
    Engine::Entity *entity = &entityArr->at(entityIndex);
    Engine::Component *positioncmp = Engine::Component::FindComponentByType("Position", entity);
    if(positioncmp->getType() == std::string("err")) {
        std::cerr << "shockbar de bz tes signatures sont rincées" << std::endl;
        return;
    }
    Engine::Component *velocitycmp = Engine::Component::FindComponentByType("Velocity", entity);
    if(velocitycmp->getType() == std::string("err")) {
        std::cerr << "shockbar de bz tes signatures sont rincées" << std::endl;
        return;
    }
    std::pair<int, int> position = positioncmp->getData<std::pair<int, int>>();
    int velocity = velocitycmp->getData<int>();
    position.first += velocity;
    if (position.first < -10 || position.first > 2000) {
        entityArr->erase(entityArr->begin() + entityIndex);
        entitiesSignature->erase(entitiesSignature->begin() + entityIndex);
    } 
    positioncmp->setData<std::pair<int, int>>(position);
}

void Rtype::Systems::shootMissile(std::vector<Engine::Entity> *entityArr, int entityIndex, Engine::eventQueue *events, std::vector<Engine::Signature> *entitiesSignature)
{
    Engine::Entity *entity = &entityArr->at(entityIndex);
    Engine::Component *controllercmp = Engine::Component::FindComponentByType("Controller", entity);
    if(controllercmp->getType() == std::string("err")) {
        std::cerr << "shockbar de bz tes signatures sont rincées" << std::endl;
        return;
    }
    Engine::Component *positioncmp = Engine::Component::FindComponentByType("Position", entity);
    if(positioncmp->getType() == std::string("err")) {
        std::cerr << "shockbar de bz tes signatures sont rincées" << std::endl;
        return;
    }
    sf::Clock *cooldown = &(Engine::Component::FindComponentByType("Shoot", entity)->getData<sf::Clock>());
    int controllerId = controllercmp->getData<int>();
    std::pair<int, int> position = positioncmp->getData<std::pair<int, int>>();
    Engine::eventQueue::iterator it = events->begin();
    while(it != events->end()) {
        if(it->getType() == SHOOT && it->getOwner() == controllerId) {
            if (cooldown->getElapsedTime().asMilliseconds() > 500) {
                cooldown->restart();
                switch (it->getValue()) {
                    case LEFT:
                        EntityFactory::buildMissileEntity(entityArr, entitiesSignature, -10, std::make_pair(position.first + 50, position.second + 20), controllerId);
                        break;
                    case RIGHT:
                        EntityFactory::buildMissileEntity(entityArr, entitiesSignature, 10, std::make_pair(position.first + 50, position.second + 20), controllerId);
                        break;
                }
            }
            it = events->erase(it);
        } else ++it;
    }
}

void Rtype::Systems::objectHit(std::vector<Engine::Entity> *entityArr, int entityIndex, Engine::eventQueue *events, std::vector<Engine::Signature> *entitiesSignature)
{
    Engine::Entity *entity = &entityArr->at(entityIndex);
    Engine::Component *positioncmp = Engine::Component::FindComponentByType("Position", entity);
    Engine::Component *sizecmp = Engine::Component::FindComponentByType("Size", entity);
    int controllerID = Engine::Component::FindComponentByType("Object", entity)->getData<int>();
    std::pair<int, int> position = positioncmp->getData<std::pair<int, int>>();
    std::pair<int, int> size = sizecmp->getData<std::pair<int, int>>();
    std::bitset<MAX_COMPONENTS> sign(PositionComponent | SizeComponent | PositionComponent | ControllerComponent);

    for (int i = 0; i < entityArr->size(); i++) {
        if (i != entityIndex && (entitiesSignature->at(i).getBits() | sign) == entitiesSignature->at(i).getBits() && Engine::Component::FindComponentByType("Controller", &entityArr->at(i))->getData<int>() != controllerID) {
            std::pair<int, int> tempPosition = Engine::Component::FindComponentByType("Position", &entityArr->at(i))->getData<std::pair<int, int>>();
            std::pair<int, int> tempSize = Engine::Component::FindComponentByType("Size", &entityArr->at(i))->getData<std::pair<int, int>>();
            if (position.first + size.first > tempPosition.first && position.first < tempPosition.first + tempSize.first && position.second + size.second > tempPosition.second && position.second < tempPosition.second + tempSize.second) {
                entityArr->erase(entityArr->begin() + i);
                entityArr->erase(entityArr->begin() + (i < entityIndex ? entityIndex - 1 : entityIndex));
                entitiesSignature->erase(entitiesSignature->begin() + i);
                entitiesSignature->erase(entitiesSignature->begin() + (i < entityIndex ? entityIndex - 1 : entityIndex));
            }
        };
    }
}
