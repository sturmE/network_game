//
//  PlayerEntity.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "PlayerEntity.h"
#include "AssetManager.h"
#include "World.h"

PlayerEntity::PlayerEntity()
{}

PlayerEntity::~PlayerEntity()
{
    onLeavingWorld();
}

void PlayerEntity::onAddedToWorld()
{
    _sprite.reset(new sf::Sprite());
    _sprite->setTexture(*getWorld()->assetManager()->getOrCreateTexture("cartman.png"));
    _sprite->setOrigin(_sprite->getLocalBounds().width / 2.0f, _sprite->getLocalBounds().height / 2.0f);    
    _sprite->setScale(0.75 * 2, 0.75 * 2);
}

void PlayerEntity::onLeavingWorld()
{
}

void PlayerEntity::setPosition(float x, float y)
{
}

void PlayerEntity::update(float dt)
{
    handleInput(dt);
}

void PlayerEntity::handleEvent(const Event& event)
{
    switch (event.type) {
    }
}

void PlayerEntity::submit(RenderQueue* renderQueue)
{
    renderQueue->push(buildSortKey(RenderLayer::World), _sprite.get());
}

void PlayerEntity::handleInput(float dt)
{
    float xAxis = 0;
    float yAxis = 0;
    bool xAxisHasDirection = false;
    bool yAxisHasDirection = false;
    bool axisHasDirection = false;
    bool buttonIsPressed = false;
    const sf::Keyboard::Key left = sf::Keyboard::Key::A;
    const sf::Keyboard::Key right = sf::Keyboard::Key::D;
    const sf::Keyboard::Key down = sf::Keyboard::Key::S;
    const sf::Keyboard::Key up = sf::Keyboard::Key::W;
    const bool leftIsPressed = sf::Keyboard::isKeyPressed(left);
    const bool rightIsPressed = sf::Keyboard::isKeyPressed(right);
    const bool upIsPressed = sf::Keyboard::isKeyPressed(up);
    const bool downIsPressed = sf::Keyboard::isKeyPressed(down);
}
