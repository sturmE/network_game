//
//  Entity.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "Entity.h"
#include "World.h"

Entity::Entity() {}
Entity::~Entity() {}

void Entity::setWorld(World* world)
{
    if (_world != world) {
        _world = world;        
    }
}

World* Entity::getWorld() { return _world; }
uint64_t Entity::getId() { return _id; }
void Entity::onAddedToWorld() {}
void Entity::onLeavingWorld() {}
void Entity::update(float dt) {}
void Entity::submit(RenderQueue* renderQueue) {};
void Entity::handleEvent(const Event& event) {}

