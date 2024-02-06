/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** EntityFactory
*/

#include "../headers/EntityFactory.hpp"

void EntityFactory::buildSpaceshipEntity(std::vector<Engine::Entity> *entities, std::vector<Engine::Signature> *signatures, int controllerId, std::pair<int,int> position)
{
    Engine::Signature signature;
    Engine::Entity spaceship;

    spaceship.push_back(ComponentsFactory::entityType(SPACESHIP));
    spaceship.push_back(ComponentsFactory::velocityComponent(10));
    spaceship.push_back(ComponentsFactory::drawableComponent());
    spaceship.push_back(ComponentsFactory::sizeComponent(std::pair<int, int>(100, 100)));
    spaceship.push_back(ComponentsFactory::controllerComponent(controllerId));
    spaceship.push_back(ComponentsFactory::positionComponent(position));
    spaceship.push_back(ComponentsFactory::shootComponent());

    std::bitset<MAX_COMPONENTS> tempSignature(EntityType | VelocityComponent | DrawableComponent | SizeComponent | ControllerComponent | PositionComponent | ShootComponent);

    signature.setBits(tempSignature);
    signatures->push_back(signature);
    entities->push_back(spaceship);
}

void EntityFactory::buildEnnemyEntity(std::vector<Engine::Entity> *entities, std::vector<Engine::Signature> *signatures, int controllerId, std::pair<int,int> position)
{
    Engine::Signature signature;
    Engine::Entity ennemy;

    ennemy.push_back(ComponentsFactory::entityType(ENNEMY));
    ennemy.push_back(ComponentsFactory::velocityComponent(10));
    ennemy.push_back(ComponentsFactory::drawableComponent());
    ennemy.push_back(ComponentsFactory::sizeComponent(std::pair<int, int>(195, 150)));
    ennemy.push_back(ComponentsFactory::controllerComponent(controllerId));
    ennemy.push_back(ComponentsFactory::positionComponent(position));
    ennemy.push_back(ComponentsFactory::shootComponent());

    std::bitset<MAX_COMPONENTS> tempSignature(EntityType | VelocityComponent | DrawableComponent | SizeComponent | ControllerComponent | PositionComponent | ShootComponent);

    signature.setBits(tempSignature);
    signatures->push_back(signature);
    entities->push_back(ennemy);
}

void EntityFactory::buildMissileEntity(std::vector<Engine::Entity> *entities, std::vector<Engine::Signature> *signatures, int velocity, std::pair<int,int> position, int controllerID)
{
    Engine::Signature signature;
    Engine::Entity missile;

    missile.push_back(ComponentsFactory::entityType(MISSILE));
    missile.push_back(ComponentsFactory::velocityComponent(velocity));
    missile.push_back(ComponentsFactory::drawableComponent());
    missile.push_back(ComponentsFactory::sizeComponent(std::pair<int, int>(64, 64)));
    missile.push_back(ComponentsFactory::objectComponent(controllerID));
    missile.push_back(ComponentsFactory::positionComponent(position));

    std::bitset<MAX_COMPONENTS> tempSignature(EntityType | VelocityComponent | DrawableComponent | SizeComponent | ObjectComponent | PositionComponent);

    signature.setBits(tempSignature);
    signatures->push_back(signature);
    entities->push_back(missile);
}