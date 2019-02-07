//
//  MessageType.hpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include <stdint.h>
#include <vector>
#include "ByteStream.hpp"

enum class MessageType : uint16_t
{
    // Client Messages
    Auth            = 1,
    Login,
    
    // Server Messages
    AuthResponse         = 32768,
    LoginResponse,
    Chat,
    Move,
    CreateObject,
};

enum class ServerMessageType : uint8_t
{
    
};

enum class ClientMessageType : uint8_t
{
    
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

struct LoginMessage : public Message
{
    LoginMessage() : Message(MessageType::Login) {}
    LoginMessage(std::string&& name) : Message(MessageType::Login), name(name) {}
    
    std::string name;
    
    void pack(ByteStream& buffer) const
    {
        Message::pack(buffer);
        buffer << name;
    }
};


struct LoginResponseMessage : public Message
{
    LoginResponseMessage() : Message(MessageType::LoginResponse) {}
    
    float position[3];
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
    ChatMessage(std::string&& contents) : Message(MessageType::Chat), contents(std::move(contents)) {}
    
    std::string contents;
    
    void pack(ByteStream& buffer) const
    {
        Message::pack(buffer);
        buffer << contents;
    }
};

enum class MoveType : uint8_t
{
    StartMoveUp,
    StartMoveDown,
    StartMoveLeft,
    StartMoveRight,
};

struct MoveMessage : public Message
{
    MoveMessage() : Message(MessageType::Move) {}
    
    uint64_t guid;
    MoveType moveType;    
};





