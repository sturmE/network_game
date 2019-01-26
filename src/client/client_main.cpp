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

const uint32_t kWindowWidth = 1600.f;
const uint32_t kWindowHeight = 900.f;
const std::string kWindowName = "dirty";

ENetHost* client;
ENetPeer* server;
std::unique_ptr<Game> game;


void pushInputEvents(std::vector<EventPtr>& events)
{
    const sf::Keyboard::Key left = sf::Keyboard::Key::A;
    const sf::Keyboard::Key right = sf::Keyboard::Key::D;
    const sf::Keyboard::Key down = sf::Keyboard::Key::S;
    const sf::Keyboard::Key up = sf::Keyboard::Key::W;
    const bool leftIsPressed = sf::Keyboard::isKeyPressed(left);
    const bool rightIsPressed = sf::Keyboard::isKeyPressed(right);
    const bool upIsPressed = sf::Keyboard::isKeyPressed(up);
    const bool downIsPressed = sf::Keyboard::isKeyPressed(down);
    
    if (leftIsPressed) {
        events.emplace_back(new KeyPressEvent(sf::Keyboard::Key::A));
    }
    if (rightIsPressed) {
        events.emplace_back(new KeyPressEvent(sf::Keyboard::Key::D));
    }
    if (upIsPressed) {
        events.emplace_back(new KeyPressEvent(sf::Keyboard::Key::W));
    }
    if (downIsPressed) {
        events.emplace_back(new KeyPressEvent(sf::Keyboard::Key::S));
    }
}

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
    
    // wait 5 seconds for connection
    if (enet_host_service(client, &enetEvent, 5000) > 0 && enetEvent.type == ENET_EVENT_TYPE_CONNECT) {
        printf("Connection to server succeeded.\n");
    } else {
        enet_peer_reset(server);
        printf("Connection to server failed.\n");
    }
    
    game.reset(new Game(server));
    
    sf::RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), kWindowName,  sf::Style::Titlebar  | sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    
    sf::Clock frameClock;
    sf::Clock gameClock;
    
    
//    std::ifstream t("settings.json");
//    std::string json_str((std::istreambuf_iterator<char>(t)),
//                    std::istreambuf_iterator<char>());
//    json settings = json::parse(json_str);
    
    
    game->onStart(&window);
    
    std::vector<EventPtr> events;
    
    bool hasFocus = true;
    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                case sf::Event::Resized: {
                    game->onWindowResize();
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
                    hasFocus = false;
                    break;
                }
                case sf::Event::GainedFocus: {
                    hasFocus = true;
                    break;
                }
                default: {
                    break;
                }
            }
        }
        
        sf::Time frameTime = frameClock.restart();
        sf::Time gameTime = gameClock.getElapsedTime();
        
        events.clear();
        if (hasFocus) {
            pushInputEvents(events);
        }
        
        // get messages from server - turn them into events and handle them in the game simulation
        while (enet_host_service(client, &enetEvent, 0) > 0) {
            switch (enetEvent.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    break;
                case ENET_EVENT_TYPE_RECEIVE: {
                    const Event* baseEvent = nullptr;
                    baseEvent = reinterpret_cast<Event*>(enetEvent.packet->data);
                    printf("Received event:%s from server\n", to_string(baseEvent->type).data());
                    switch (baseEvent->type) {
                        case EventType::OnConnect: {
                            events.emplace_back(event::deserialize<OnConnectEvent>(baseEvent));
                            break;
                        }
                        case EventType::PositionUpdate: {
                            events.emplace_back(event::deserialize<PositionUpdateEvent>(baseEvent));
                            break;
                        }
                        case EventType::CreateEntity: {
                            events.emplace_back(event::deserialize<CreateEntityEvent>(baseEvent));
                            break;
                        }
                        case EventType::DestroyEntity: {
                            events.emplace_back(event::deserialize<DestroyEntityEvent>(baseEvent));
                            break;
                        }
                    }
                    enet_packet_destroy(enetEvent.packet);
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT:
                    break;
                default:
                    break;
            }
        }

        
        window.clear(sf::Color::Black);
        
        game->onFrame(events, frameTime.asSeconds());
        
        window.display();
    }
    game->onShutdown();
    
    ENetEvent event;
    enet_peer_disconnect(server, 0);
    
    while (enet_host_service (client, & event, 3000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("Disconnection succeeded.");
                break;
            default:
                printf("unhandled event type");
                break;
        }
    }
    enet_peer_reset(server);
    
    return 0;
}

