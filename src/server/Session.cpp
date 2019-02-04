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
        const MessageType type = packet.messageType();
        
        switch (type) {
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

void Session::handleChatMessage(const Packet& packet)
{
    Packet copy = packet;
    _world->broadcastPacket(std::move(copy));
}

void Session::sendPacket(Packet&& packet)
{
    _connection->queueOutgoing(std::move(packet));
}
