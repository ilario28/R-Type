/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Systems
*/

#pragma once

#include <GameEngine>
#include "ComponentsFactory.hpp"

enum eventType {
    ERR = -1,
    MOVE = 0,
    SHOOT,
};

enum MoveTypes {
    UP,
    LEFT,
    RIGHT,
    DOWN
};

namespace Rtype {
    namespace Systems {
        void buildGameSystems(std::vector<Engine::System> *systems);
        void moveEntityByController(std::vector<Engine::Entity> *entityArr, int entityIndex, Engine::eventQueue *events, std::vector<Engine::Signature> *entitiesSignature);
        void shootMissile(std::vector<Engine::Entity> *entityArr, int entityIndex, Engine::eventQueue *events, std::vector<Engine::Signature> *entitiesSignature);
        void moveEntityByInertia(std::vector<Engine::Entity> *entityArr, int entityIndex, Engine::eventQueue *events, std::vector<Engine::Signature> *entitiesSignature);
        void objectHit(std::vector<Engine::Entity> *entityArr, int entityIndex, Engine::eventQueue *events, std::vector<Engine::Signature> *entitiesSignature);
    };
}
