//
//  WorldSessionManager.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#include "WorldSessionManager.hpp"

WorldSessionManager::WorldSessionManager()
{}

void WorldSessionManager::addSession(const std::shared_ptr<WorldSession>& session)
{
    std::lock_guard<std::mutex> lock(_sessionsMutex);
    _sessionsToAdd.emplace_back(session);
}

void WorldSessionManager::visitSessions(std::function<void(WorldSession*)> visitor)
{
    {
        std::lock_guard<std::mutex> lock(_sessionsMutex);
        _sessions.insert(end(_sessions), begin(_sessionsToAdd), end(_sessionsToAdd));
        _sessionsToAdd.clear();
    }
    
    for (auto& session : _sessions) {
        visitor(session.get());
    }
}
