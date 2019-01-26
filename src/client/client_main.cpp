//
//  main.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <json.hpp>
#include <string>
#include <fstream>
#include <streambuf>
#include <enet/enet.h>
using json = nlohmann::json;

const uint32_t kWindowWidth = 1600.f * 2.f;
const uint32_t kWindowHeight = 900.f * 2.f;
const std::string kWindowName = "dirty";

ENetHost* client;
ENetPeer* server;
Game game;

int main(int argc, char** argv) {
    client = enet_host_create (NULL /* create a client host */,
                                1 /* only allow 1 outgoing connection */,
                                2 /* allow up 2 channels to be used, 0 and 1 */,
                                0 /* assume any amount of incoming bandwidth */,
                                0 /* assume any amount of incoming bandwidth */);
    if (client == NULL) {
        fprintf (stderr, "An error occurred while trying to create an ENet client host.\n");
        exit(EXIT_FAILURE);
    }
    
    ENetAddress address;
    ENetEvent enetEvent;
    
    // this should be defined by settings json
    enet_address_set_host(&address, "localhost");
    address.port = 44951;
    server = enet_host_connect(client, & address, 2, 0);
    if (server == NULL) {
        fprintf (stderr, "No available peers for initiating an ENet connection.\n");
        exit(EXIT_FAILURE);
    }
    
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(client, & enetEvent, 5000) > 0 && enetEvent.type == ENET_EVENT_TYPE_CONNECT) {
        printf("Connection to localhost:1234 succeeded.\n");
    } else {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(server);
        printf("Connection to localhost:1234 failed.\n");
    }
    
    
    sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), kWindowName,  sf::Style::Titlebar  | sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    
    sf::Clock frameClock;
    sf::Clock gameClock;
    
    
//    std::ifstream t("settings.json");
//    std::string json_str((std::istreambuf_iterator<char>(t)),
//                    std::istreambuf_iterator<char>());
//    json settings = json::parse(json_str);
    
    
    game.onStart(&window);
    
    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                case sf::Event::Resized: {
                    game.onWindowResize();
                    break;
                }
                case sf::Event::KeyPressed: {
                    if (event.key.code == sf::Keyboard::Key::Escape) {
                        window.close();
                    }
                    
                    break;
                }
                case sf::Event::KeyReleased: {
                    break;
                }
                case sf::Event::LostFocus: {
                    break;
                }
                case sf::Event::GainedFocus: {
                    break;
                }
                default: {
                    break;
                }
            }
        }
        
        sf::Time frameTime = frameClock.restart();
        sf::Time gameTime = gameClock.getElapsedTime();
        
        ENetPacket* packet = enet_packet_create("packet", strlen ("packet") + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(server, 0, packet);
        
        while (enet_host_service(client, &enetEvent, 0) > 0) {
            switch (enetEvent.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    printf("received packet\n");
                    enet_packet_destroy(enetEvent.packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    break;
                default:
                    break;
            }
        }
        
        
        

        
        window.clear(sf::Color::Black);
        game.onFrame(frameTime.asSeconds());
        window.display();
    }
    game.onShutdown();
    
    return 0;
}

