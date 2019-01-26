//
//  World.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include "RenderContext.h"

class AssetManager;
class Entity;
using EntityId = uint64_t;
using EntityPtr = std::shared_ptr<Entity>;

class World
{
private:
    AssetManager* _assetManager { nullptr };
    
    std::vector<EntityPtr> _entities;
    std::map<EntityId, EntityPtr> _entityMap;
public:
    World(AssetManager* am);
    ~World();

    EntityPtr getEntity(EntityId entityId);
    void removeEntity(Entity* entity);
    bool addEntity(const EntityPtr& e);
    void simulate(float dt);
    void submit(const RenderContext& renderContext);
    
    AssetManager* assetManager() { return _assetManager; }
};
