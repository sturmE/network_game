//
//  RenderQueue.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "RenderItem.h"

class RenderQueue {
private:
    std::vector<RenderItem> _renderItems;
public:
    void push(uint32_t sortKey, sf::Drawable* drawable, const char* debugString = "");
    void render(sf::RenderWindow* window);
};

