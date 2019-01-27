//
//  MessageType.hpp
//  dirtycommon
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

enum class MessageType : uint16_t
{
    // Client Messages
    Connect         = 1,
    Disconnect      = 2,
    
    // Server Messages
    BeginSession    = 32768,
    EndSession      = 32769,
};

struct Message
{
    Message(MessageType type) : type(type) {}
    
    MessageType type;
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
