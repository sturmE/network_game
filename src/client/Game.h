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

class Game
{
private:
    RenderQueue _renderQueue;
    std::unique_ptr<World> _world;
    std::unique_ptr<AssetManager> _assetManager;
    sf::View _mainView;
    sf::RenderWindow* _renderWindow{nullptr};
public:
    Game();
    void onWindowResize();
    void onStart(sf::RenderWindow* renderWindow);
    void onFrame(float dt);
    void onShutdown();
};

