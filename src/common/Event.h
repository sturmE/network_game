//
//  Event.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include <stdint.h>
#include <vector>
#include <string>
#include <memory>
#include "EntityType.h"

enum class EventType : uint8_t
{
    Unknown = 0,
    CreateEntity = 1,
    DestroyEntity = 2,
    PositionUpdate = 3,
    KeyPress = 4,
    OnConnect = 5,
};

std::string_view to_string(EventType type);

struct Event
{
    Event(EventType type) : type(type) {}
    
    const EventType type;
};

using EventPtr = std::shared_ptr<Event>;

struct KeyPressEvent : public Event
{
    KeyPressEvent(uint32_t keyCode)
    : Event(EventType::KeyPress)
    , keyCode(keyCode)
    {}
    
    uint32_t keyCode;
};

struct OnConnectEvent : public Event
{
    OnConnectEvent(uint64_t entityId, std::vector<std::pair<uint64_t, EntityType>>&& entities)
    : Event(EventType::OnConnect)
    , entityId(entityId)
    , entities(entities)
    {}
    
    uint64_t entityId;
    std::vector<std::pair<uint64_t, EntityType>> entities;
};

struct CreateEntityEvent : public Event
{
    CreateEntityEvent(uint64_t entityId, EntityType type)
    : Event(EventType::CreateEntity)
    , entityId(entityId)
    , entityType(type)
    {}
    
    uint64_t entityId;
    EntityType entityType;
};

struct DestroyEntityEvent : public Event
{
    DestroyEntityEvent(uint64_t entityId)
    : Event(EventType::CreateEntity)
    , entityId(entityId)
    {}
    
    uint64_t entityId;
};

struct PositionUpdateEvent : public Event
{
    PositionUpdateEvent(uint64_t objectId, float x, float y)
    : Event(EventType::PositionUpdate)
    , objectId(objectId)
    , x(x)
    , y(y)
    {}
    
    uint64_t objectId;
    float x;
    float y;
};

class event
{
public:
    template <typename T>
    static void serialize(const T& event, std::vector<uint8_t>& buffer)
    {
        buffer.resize(sizeof(T));
        memcpy(buffer.data(), &event, sizeof(T));
    }

    template <typename T>
    static T* deserialize(const Event* event)
    {
        return new T(*((T*)event));
    }        
};

