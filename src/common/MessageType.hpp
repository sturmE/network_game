//
//  MessageType.hpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include <stdint.h>
#include <vector>
#include "Bytebuffer.hpp"

enum class MessageType : uint16_t
{
    // Client Messages
    Auth            = 1,
    
    // Server Messages
    AuthResponse         = 32768,
    Chat,
};


const char* to_string(MessageType type);

struct Message
{
    Message(MessageType type) : type(type) {}
    
    const MessageType type;
    
    void pack(ByteStream& buffer) const
    {
        buffer << type;
    }
};

struct AuthMessage : public Message
{
    AuthMessage() : Message(MessageType::Auth) {}
};

struct AuthResponseMessage : public Message
{
    AuthResponseMessage() : Message(MessageType::AuthResponse) {}
    
    uint64_t sessionId;
    
    void pack(ByteStream& buffer) const
    {
        Message::pack(buffer);
        buffer << sessionId;
    }
};

struct ChatMessage : public Message
{
    ChatMessage() : Message(MessageType::Chat) {}
    
    std::string contents;
    
    void pack(ByteStream& buffer) const
    {
        Message::pack(buffer);
        buffer << contents;
    }
};





