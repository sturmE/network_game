//
//  World.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/3/19.
//

#pragma once

#include <vector>
#include "Packet.hpp"
#include "WorldServices.hpp"
#include "CharacterDatabase.hpp"
#include "Map.hpp"
#include "GuidProvider.hpp"

class Session;
using SessionPtr = std::shared_ptr<Session>;
class Database;
using DatabasePtr = std::shared_ptr<Database>;

class World
{
private:
    std::vector<SessionPtr> _sessions;
    std::unique_ptr<WorldServices> _services;
    std::unique_ptr<Map> _map;
    std::unique_ptr<GuidProvider> _guidProvider;
    
    DatabasePtr _db;
    std::unique_ptr<CharacterDatabase> _charDb;
public:
    World(const DatabasePtr& db);
    
    void addSession(const SessionPtr& session);
    
    void update();
    
    void broadcastPacket(Packet&& packet);
    
    WorldServices* services() { return _services.get(); }
    Map* map() { return _map.get(); }
    GuidProvider* guidProvider() { return _guidProvider.get(); }
};
