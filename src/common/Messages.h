//
//  Messages.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include <stdint.h>

enum class MessageType : uint8_t
{
    SetPosition
};

struct Message
{
    Message(MessageType type) : type(type) {}
    MessageType type;
};

struct SetPositionMessage : public Message
{
    SetPositionMessage(uint64_t objectId, float x, float y)
    : Message(MessageType::SetPosition)
    , objectId(objectId)
    , x(x)
    , y(y)
    {}
    
    uint64_t objectId;
    float x;
    float y;
};
