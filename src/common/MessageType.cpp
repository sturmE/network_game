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
        case MessageType::Auth: return "Auth";
        case MessageType::AuthResponse: return "AuthResponse";
        case MessageType::Chat: return "Chat";
    }
    return "[messageType]";
}
