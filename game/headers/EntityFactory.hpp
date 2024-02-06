/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** EntityFactory
*/

#pragma once
#include <GameEngine>
#include "ComponentsFactory.hpp"

class EntityFactory {
    public:
        static void buildSpaceshipEntity(std::vector<Engine::Entity> *entities, std::vector<Engine::Signature> *signatures, int controllerId, std::pair<int,int> position);
        static void buildEnnemyEntity(std::vector<Engine::Entity> *entities, std::vector<Engine::Signature> *signatures, int controllerId, std::pair<int,int> position);
        static void buildMissileEntity(std::vector<Engine::Entity> *entities, std::vector<Engine::Signature> *signatures, int velocity, std::pair<int,int> position, int controllerID);
};
