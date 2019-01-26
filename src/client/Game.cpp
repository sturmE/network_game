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
    
    
    std::shared_ptr<PlayerEntity> e(new PlayerEntity());
    _world->addEntity(e);
    
    // setup view
    onWindowResize();
    _mainView.setCenter(0, 0);
    _renderWindow->setView(_mainView);
}

void Game::onFrame(float dt)
{
    RenderContext renderContext;
    renderContext.renderQueue = &_renderQueue;
    renderContext.view = &_mainView;
            
    _world->simulate(dt);
    _world->submit(renderContext);
    _renderQueue.render(_renderWindow);    
}

void Game::onShutdown()
{
    _world.reset();
}
