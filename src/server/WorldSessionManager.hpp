//
//  WorldSessionManager.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 1/26/19.
//

#pragma once

#include <vector>
#include <functional>
#include <mutex>

class WorldSession;

class WorldSessionManager
{
private:
    std::mutex _sessionsMutex;
    std::vector<std::shared_ptr<WorldSession>> _sessionsToAdd;
    std::vector<std::shared_ptr<WorldSession>> _sessions;
public:
    WorldSessionManager();
    
    void addSession(const std::shared_ptr<WorldSession>& session);
    void visitSessions(std::function<void(WorldSession*)> visitor);
};
