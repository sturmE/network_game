//
//  World.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "World.h"
#include "Entity.h"
#include "Game.h"

World::World(AssetManager* am, Network* nw)
: _assetManager(am)
, _network(nw)
{}

World::~World() {
    for (auto e: _entities) {
        e->onLeavingWorld();
        e->setWorld(nullptr);
    }
}

EntityPtr World::getEntity(EntityId entityId) {
    auto it = _entityMap.find(entityId);
    if (it != end(_entityMap)) {
        return it->second;
    }
    return nullptr;
}

void World::removeEntity(Entity* entity)
{
    for(auto it = _entities.begin(); it != _entities.end(); ++it) {
        if(it->get() == entity) {
            _entities.erase(it);
            break;
        }
    }

    for(auto it = _entityMap.begin(); it != _entityMap.end(); ++it) {
        if(it->second.get() == entity) {
            _entityMap.erase(it);
            break;
        }
    }
}

bool World::addEntity(const EntityPtr& e)
{
    if (getEntity(e->getId()) == nullptr) {
        _entities.push_back(e);
        _entityMap.emplace(e->getId(), e);
        
        e->setWorld(this);
        e->onAddedToWorld();
        
        return true;
    } else {
        printf("Entity with id:%ld already exists\n", e->getId());
    }
    return false;
}

void World::simulate(float dt)
{
    for (const EntityPtr& entity : _entities) {
        entity->update(dt);
    }
}

void World::submit(const RenderContext& renderContext)
{
    for (const EntityPtr& entity : _entities) {
        entity->submit(renderContext.renderQueue);
    }
}

