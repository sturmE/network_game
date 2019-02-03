//
//  main.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//


#include "Socket.hpp"
#include "Connection.hpp"
#include <iostream>
#include <variant>


int main(int argc, char** argv)
{
    
    Socket socket;
    ConnectionPtr connection = socket.connect("localhost", 44951);
    while (connection->connectionState() != ConnectionState::Connected) {}
    
    std::cout << "Connected\n";
    
    connection->queueOutgoing(Packet(AuthMessage()));
    Packet incoming;
    while ( (incoming = connection->waitForIncoming()).messageType() != MessageType::AuthResponse) {
        std::cout << to_string(incoming.messageType()) << std::endl;
    }
    
    std::cout << "Authed\n";
        
    
    std::vector<Packet> packets;
    while (true) {
        packets.clear();
        connection->drainIncomingQueue(&packets);
    }
}
