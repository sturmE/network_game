//
//  main.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "World.hpp"
#include "WorldSocket.hpp"
#include "WorldSessionManager.hpp"

int main(int argc, char** argv)
{
    WorldSessionManager sessionManager;
    WorldSocket socket(&sessionManager);
    World world(&socket, &sessionManager);
    
    if (socket.start() == false) {
        return EXIT_FAILURE;
    }
    
    while (true) {
        world.update(0);
    }
}

