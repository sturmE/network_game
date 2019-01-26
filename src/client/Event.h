//
//  Event.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

enum class EventType : uint8_t
{
};

struct Event
{
    Event(EventType type) : type(type) {}
    
    const EventType type;
};

