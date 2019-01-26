//
//  RenderQueue.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "RenderQueue.h"
#include "RenderLayer.h"

void RenderQueue::push(uint32_t sortKey, sf::Drawable* drawable, const char* debugString)
{
    _renderItems.emplace_back(sortKey, drawable, debugString);
}

void RenderQueue::render(sf::RenderWindow* window)
{
    std::sort(begin(_renderItems), end(_renderItems),
              [](const RenderItem& lhs, const RenderItem& rhs) {
                  return lhs.sortKey < rhs.sortKey;
              });
    
    for (const RenderItem& renderItem : _renderItems) {        
        window->draw(*renderItem.drawable);
    }
    
    _renderItems.clear();
}
