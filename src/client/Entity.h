//
//  Entity.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include "RenderQueue.h"
#include "Event.h"
#include "World.h"
#include "EntityType.h"
#include <Messages.h>

using EntityId = uint64_t;

class World;

class Entity {
private:
    static EntityId createId() {
        static uint64_t key = 0;
        return ++key;
    };

    const EntityId _id{createId()};

    
public:
    // "components"
    World* _world {nullptr};
    sf::Sprite* _sprite{nullptr};
public:
    Entity();
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
    virtual void handleEvent(const Event& event);
protected:
};

using EntityPtr = std::shared_ptr<Entity>;
