/*
** EPITECH PROJECT, 2023
** B-CPP-500-MPL-5-1-rtype-guillaume.boudaille
** File description:
** Composants
*/

#pragma once

#include <GameEngine>
#include <SFML/System/Clock.hpp>

enum EntityList {
    SPACESHIP,
    MISSILE,
    ENNEMY,
};

enum ComponentTypes {
    EntityType          = 1,
    VelocityComponent   = 1 << 1,
    DrawableComponent   = 1 << 2,
    SizeComponent       = 1 << 3,
    ControllerComponent = 1 << 4,
    PositionComponent   = 1 << 5,
    ObjectComponent     = 1 << 6,
    ShootComponent      = 1 << 7,
};

class ComponentsFactory
{
    public:
        static Engine::Component entityType(EntityList entityType) { return Engine::Component(entityType, "EntityType"); }
        static Engine::Component velocityComponent(int velocity) { return Engine::Component(velocity, "Velocity"); };
        static Engine::Component drawableComponent() { return Engine::Component(true, "Drawable"); };
        static Engine::Component sizeComponent(std::pair<int, int> widthHeightSize) { return Engine::Component(widthHeightSize, "Size"); };
        static Engine::Component controllerComponent(int controller) { return Engine::Component(controller, "Controller"); };
        static Engine::Component positionComponent(std::pair<int, int> XYPosition) { return Engine::Component(XYPosition, "Position"); };
        static Engine::Component objectComponent(int controller) { return Engine::Component(controller, "Object"); };
        static Engine::Component shootComponent() { sf::Clock clock; return Engine::Component(clock, "Shoot"); };
};
