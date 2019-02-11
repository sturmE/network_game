//
//  World.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/3/19.
//

#include "World.hpp"
#include "Session.hpp"
#include "WorldServices.hpp"
#include "CharacterDatabase.hpp"

World::World(const DatabasePtr& db)
: _services(new WorldServices())
, _db(db)
, _charDb(new CharacterDatabase(_db))
{
    _services->setCharacterDatabase(_charDb.get());
    _guidProvider.reset(new GuidProvider(_charDb->getMaxGuid()));
    _map.reset(new Map());
}

void World::addSession(const SessionPtr& session)
{
    session->setWorld(this);
    _sessions.emplace_back(session);
}

void World::update()
{
    std::vector<Packet> packets;
    for (SessionPtr& session : _sessions) {
        session->processIncoming();
    }
}

void World::broadcastPacket(Packet&& packet)
{
    Packet p = std::move(packet);
    for (SessionPtr& session : _sessions) {
        Packet copy = p;
        session->sendPacket(std::move(copy));
    }
}
