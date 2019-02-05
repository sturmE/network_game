//
//  Session.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/3/19.
//

#include "Session.hpp"
#include "Connection.hpp"
#include "World.hpp"

Session::Session(const ConnectionPtr& connection)
: _connection(connection)
{
}

void Session::setWorld(World* world)
{
    _world = world;
}

void Session::processIncoming()
{
    std::optional<Packet> packetResult;
    while ((packetResult = _connection->dequeueIncoming()).has_value()) {
        Packet& packet = packetResult.value();
        const MessageType type = packet.read<MessageType>();
        
        
        switch (type) {
            case MessageType::Login: {
                handleLoginMessage(packet);
                break;
            }
            case MessageType::Chat: {
                handleChatMessage(packet);
                break;
            }
            case MessageType::Move: {
                break;
            }
            default: {
                break;
            }
        }
    }
}

void Session::handleLoginMessage(Packet& packet)
{
    std::string name;
    packet >> name;
    
    const bool exists = false;
    
    
    
    float position[3] = {0, 0, 0};
    if (exists) {
        
    } else {
        
    }
    
    Packet response;
    response << MessageType::LoginResponse;
    response.write(position, sizeof(float) * 3);
    
    sendPacket(std::move(response));
}

void Session::handleChatMessage(Packet& packet)
{
    Packet copy = packet;
    _world->broadcastPacket(std::move(copy));
}

void Session::sendPacket(Packet&& packet)
{
    _connection->queueOutgoing(std::move(packet));
}
