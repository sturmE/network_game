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
    const sf::Keyboard::Key left = sf::Keyboard::Key::A;
    const sf::Keyboard::Key right = sf::Keyboard::Key::D;
    const sf::Keyboard::Key down = sf::Keyboard::Key::S;
    const sf::Keyboard::Key up = sf::Keyboard::Key::W;
    const bool leftIsPressed = sf::Keyboard::isKeyPressed(left);
    const bool rightIsPressed = sf::Keyboard::isKeyPressed(right);
    const bool upIsPressed = sf::Keyboard::isKeyPressed(up);
    const bool downIsPressed = sf::Keyboard::isKeyPressed(down);
    
    float x = 0;
    float y = 0;
    if (leftIsPressed) {
        x += -100.f;
    }
    
    if (upIsPressed) {
        y += -100.f;
    }
    
    if (rightIsPressed) {
        x += 100.f;
    }
    
    if (downIsPressed) {
        y += 100.f;
    }
    
    if (x > 0 || y > 0) {
        sf::Vector2f newPosition = _sprite->getPosition() + sf::Vector2f(x, y) * dt;
        _sprite->setPosition(newPosition.x, newPosition.y);
    
        emitEvent(PositionUpdateEvent(getId(), newPosition.x, newPosition.y));
    }
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
