//
//  main.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "Socket.hpp"
#include "Connection.hpp"
#include <iostream>
#include <SDL.h>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) != 0) {
        std::cout << "SDL Init Failed:" << SDL_GetError();
        return EXIT_FAILURE;
    }
    atexit(SDL_Quit);
    
    uint32_t windowWidth = 1200;
    uint32_t windowHeight = 800;
    SDL_Window* window = SDL_CreateWindow("dirty", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cout << "SDL could not create window:" << SDL_GetError();
        return EXIT_FAILURE;
    }
        
    SDL_Event e;
    bool shouldQuit = false;
    while (shouldQuit == false) {
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT: {
                    shouldQuit = true;
                    break;
                }
                case SDL_WINDOWEVENT: {
                    break;
                }
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_CONTROLLERBUTTONDOWN:
                case SDL_CONTROLLERBUTTONUP:
                case SDL_CONTROLLERAXISMOTION: {
                    break;
                }
            }
        }
    }
    
    Socket socket;
    ConnectionPtr connection = socket.connect("localhost", 44951);
    
    connection->waitForConnectionState(ConnectionState::Connected);
    
    std::cout << "Connected\n";
    
    connection->queueOutgoing(Packet(AuthMessage()));
    Packet incoming;
    while ( (incoming = connection->waitForIncoming()).messageType() != MessageType::AuthResponse) {
        std::cout << to_string(incoming.messageType()) << std::endl;
    }
    
    std::cout << "Authed\n";
    
    connection->queueOutgoing(Packet(ChatMessage("Hi, rawr")));
    
    while (true) {
        std::optional<Packet> packetResult;
        while ( (packetResult = connection->dequeueIncoming()).has_value() ) {
            Packet& packet = packetResult.value();
            
            std::cout << "Received " << to_string(packet.messageType()) << std::endl;
        }
    }
    
    SDL_DestroyWindow(window);
    return EXIT_SUCCESS;
}
