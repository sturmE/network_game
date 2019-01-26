//
//  Event.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include <stdint.h>
#include <vector>

enum class EventType : uint8_t
{
    PositionUpdate = 1
};

struct Event
{
    Event(EventType type) : type(type) {}
    
    const EventType type;
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
    
    void serialize(std::vector<uint8_t>& buffer) const
    {
        buffer.resize(sizeof(PositionUpdateEvent));
        memcpy(buffer.data(), this, sizeof(PositionUpdateEvent));
    }
};

