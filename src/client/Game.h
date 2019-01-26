//
//  Game.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include "World.h"
#include <memory>
#include "RenderQueue.h"
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <enet/enet.h>


class PlayerEntity;
class Network;
class Event;
using EventPtr = std::shared_ptr<Event>;

class Game
{
private:
    std::shared_ptr<PlayerEntity> _player;
    std::unique_ptr<Network> _network;
    RenderQueue _renderQueue;
    std::unique_ptr<World> _world;
    std::unique_ptr<AssetManager> _assetManager;
    sf::View _mainView;
    sf::RenderWindow* _renderWindow{nullptr};
public:
    Game(ENetPeer* server);
    void onWindowResize();
    void onStart(sf::RenderWindow* renderWindow);
    void onFrame(const std::vector<EventPtr>& events, float dt);
    void onShutdown();
};

