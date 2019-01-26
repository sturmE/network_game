//
//  PlayerEntity.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "PlayerEntity.h"
#include "AssetManager.h"
#include "World.h"
#include "Event.h"

PlayerEntity::PlayerEntity(uint64_t entityId)
: Entity(entityId)
{}

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
    if (_x > 0 || _y > 0) {
        sf::Vector2f newPosition = _sprite->getPosition() + sf::Vector2f(_x, _y) * dt;
        _sprite->setPosition(newPosition.x, newPosition.y);
    
        _world->emitEvent(PositionUpdateEvent(getId(), newPosition.x, newPosition.y));
    }
    _x = 0;
    _y = 0;
}

void PlayerEntity::handleEvent(const Event* event)
{
    switch (event->type) {
        case EventType::KeyPress: {
            KeyPressEvent* keyEvent = (KeyPressEvent*)event;
            switch (keyEvent->keyCode) {
                case sf::Keyboard::Key::W: {
                    _y += 100;
                    break;
                }
                case sf::Keyboard::Key::A: {
                    _x -= 100;
                    break;
                }
                case sf::Keyboard::Key::S: {
                    _y -= 100;
                    break;
                }
                case sf::Keyboard::Key::D: {
                    _x += 100;
                    break;
                }
            }
            break;
        }
        case EventType::PositionUpdate: {
            PositionUpdateEvent* positionEvent = (PositionUpdateEvent*)event;
            _sprite->setPosition(positionEvent->x, positionEvent->y);
            break;
        }
        default: {
            printf("PlayerEntity received unexpected event:%s\n", to_string(event->type).data());
            break;
        }
    }
}

void PlayerEntity::submit(RenderQueue* renderQueue)
{
    renderQueue->push(buildSortKey(RenderLayer::World), _sprite.get());
}
