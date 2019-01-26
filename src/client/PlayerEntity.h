//
//  PlayerEntity.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include "Entity.h"
#include "SFMLTypes.h"

class Event;

class PlayerEntity : public Entity
{
public:
    PlayerEntity();
    PlayerEntity(uint64_t entityId);
    virtual ~PlayerEntity();
    
    virtual EntityType getType() final { return EntityType::Player; }
    
    virtual void onAddedToWorld() final;
    virtual void onLeavingWorld() final;
    virtual void update(float dt) final;
    virtual void handleEvent(const Event* event) final;
    virtual void submit(RenderQueue* renderQueue) final;
    virtual void setPosition(float x, float y) final;
private:
    float _x { 0 };
    float _y { 0 };
    SpritePtr _sprite;
};
