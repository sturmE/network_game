//
//  Game.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "Game.h"
#include "World.h"
#include <SFML/Graphics.hpp>
#include "RenderContext.h"
#include "PlayerEntity.h"
#include "Network.h"

Game::Game(ENetPeer* server)
: _network(new Network(server))
{}

void Game::onWindowResize()
{
    sf::Vector2u windowSize = _renderWindow->getSize();
    _mainView.setSize(windowSize.x, windowSize.y);
}

void Game::onStart(sf::RenderWindow* window)
{
    _assetManager.reset(new AssetManager("Asdf"));
    
    _renderWindow = window;
    // setup world
    _world.reset(new World(_assetManager.get(), _network.get()));
    
    
    
    
    // setup view
    onWindowResize();
    _mainView.setCenter(0, 0);
    _renderWindow->setView(_mainView);
}

void Game::onFrame(const std::vector<EventPtr>& events, float dt)
{
    RenderContext renderContext;
    renderContext.renderQueue = &_renderQueue;
    renderContext.view = &_mainView;
    
    for (const EventPtr& event : events) {
        switch (event->type) {
            case EventType::OnConnect: {
                OnConnectEvent* connectEvent = (OnConnectEvent*)event.get();
                _player.reset(new PlayerEntity(connectEvent->entityId));
                _world->addEntity(_player);
                _network->sendMessage(CreateEntityEvent(_player->getId(), EntityType::Player));
                
                for (auto& p : connectEvent->entities) {
                    _world->addEntity(EntityPtr(new PlayerEntity(p.first)));
                }
                
                break;
            }
            case EventType::KeyPress: {
                _player->handleEvent(event.get());
                break;
            }
            case EventType::CreateEntity: {
                CreateEntityEvent* createEvent = (CreateEntityEvent*)event.get();
                switch (createEvent->entityType) {
                    case EntityType::Player: {
                        _world->addEntity(EntityPtr(new PlayerEntity(createEvent->entityId)));
                        break;
                    }
                }
                break;
            }
            case EventType::DestroyEntity: {
                DestroyEntityEvent* destroyEvent = (DestroyEntityEvent*)event.get();
                EntityPtr entity = _world->getEntity(destroyEvent->entityId);
                if (entity) {
                    _world->removeEntity(entity.get());
                } else {
                    printf("Failed to remove entity of id:%lld\n", destroyEvent->entityId);
                }
                break;
            }
            case EventType::PositionUpdate: {
                PositionUpdateEvent* positionEvent = (PositionUpdateEvent*)event.get();
                EntityPtr entity = _world->getEntity(positionEvent->objectId);
                if (entity) {
                    entity->handleEvent(event.get());
                } else {
                    printf("Failed to find entity of id:%lld for position event\n", positionEvent->objectId);
                }
                break;
            }
            case EventType::Unknown: {
                printf("Unknown event\n");
                break;
            }
        }
    }
                
    _world->simulate(dt);
    _world->submit(renderContext);
    _renderQueue.render(_renderWindow);    
}

void Game::onShutdown()
{
    _world.reset();
}
