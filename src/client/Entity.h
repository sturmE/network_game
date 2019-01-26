//
//  Entity.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include "RenderQueue.h"
#include "EntityType.h"

using EntityId = uint64_t;

class Event;
class World;

class Entity {
private:    
    const EntityId _id;
public:
    // "components"
    World* _world {nullptr};
    sf::Sprite* _sprite{nullptr};
public:
    Entity();
    Entity(uint64_t entityId);
    virtual ~Entity();
    
    void setWorld(World* world);

    World* getWorld();
    uint64_t getId();
    
    // should only be called by World object
    virtual void onAddedToWorld();
    virtual void onLeavingWorld();
    // -----
    
    
    virtual EntityType getType() = 0;
    virtual void setPosition(float x, float y) {};
    
    virtual void update(float dt);
    virtual void submit(RenderQueue* renderQueue);
    virtual void handleEvent(const Event* event);
};

using EntityPtr = std::shared_ptr<Entity>;
