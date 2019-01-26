//
//  Entity.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "Entity.h"
#include "World.h"

static EntityId createId()
{
    static uint64_t key = 0;
    return ++key;
};

Entity::Entity() : _id(createId()) {}
Entity::Entity(uint64_t entityId) : _id(entityId) {}

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
void Entity::handleEvent(const Event* event) {}

//void Entity::emitEvent(const std::shared_ptr<Event>& event)
//{
//    _world->emitEvent(*event.get());
//}

