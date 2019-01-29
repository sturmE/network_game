//
//  MessageType.cpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/27/19.
//

#include "MessageType.hpp"

const char* to_string(MessageType type)
{
    switch (type) {
        case MessageType::Connect: return "Connect";
        case MessageType::Disconnect: return "Disconnect";
        case MessageType::BeginSession: return "BeginSession";
        case MessageType::EndSession: return "EndSession";
    }
    return nullptr;
}
