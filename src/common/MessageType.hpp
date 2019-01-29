//
//  MessageType.hpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include <stdint.h>
#include <vector>

enum class MessageType : uint16_t
{
    // Client Messages
    Connect         = 1,
    Disconnect      = 2,
    
    // Server Messages
    BeginSession    = 32768,
    EndSession      = 32769,
};

const char* to_string(MessageType type);

struct Message
{
    Message(MessageType type) : type(type) {}
    
    const MessageType type;
    
    template <typename T>
    static void serialize(const T& msg, std::vector<uint8_t>& buffer)
    {        
        buffer.resize(sizeof(T));
        memcpy(buffer.data(), &msg, sizeof(T));
    }
};

struct ConnectMsg : public Message
{
    ConnectMsg() : Message(MessageType::Connect) {}
};

struct BeginSession : public Message
{
    BeginSession() : Message(MessageType::BeginSession) {}
};

struct EndSession : public Message
{
    EndSession() : Message(MessageType::EndSession) {}
};
