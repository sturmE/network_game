//
//  World.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include "RenderContext.h"
#include "Network.h"

class Event;
class AssetManager;
class Entity;
using EntityId = uint64_t;
using EntityPtr = std::shared_ptr<Entity>;

class World
{
private:
    AssetManager* _assetManager { nullptr };
    Network* _network { nullptr };
    
    std::vector<std::shared_ptr<Event>> _events;
    std::vector<EntityPtr> _entities;
    std::map<EntityId, EntityPtr> _entityMap;
public:
    World(AssetManager* am, Network* nw);
    ~World();

    EntityPtr getEntity(EntityId entityId);
    void removeEntity(Entity* entity);
    bool addEntity(const EntityPtr& e);
    void simulate(float dt);
    void submit(const RenderContext& renderContext);
    
    template <typename T>
    void emitEvent(const T& event);
    
    AssetManager* assetManager() { return _assetManager; }
};

template <typename T>
void World::emitEvent(const T& event)
{
    _network->sendMessage(event);
}
