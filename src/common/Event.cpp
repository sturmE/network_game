//
//  Messages.cpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "Event.h"

std::string_view to_string(EventType type)
{
    switch (type) {
        case EventType::Unknown:
            return "Unknown";
        case EventType::PositionUpdate:
            return "PositionUpdate";
        case EventType::CreateEntity:
            return "CreateEntity";
        case EventType::DestroyEntity:
            return "DestroyEntity";
        default:
            return "err";
    }
    return "err";
}


