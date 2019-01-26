//
//  RenderItem.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "SFMLTypes.h"
#include "RenderLayer.h"

struct RenderItem
{
    RenderItem(RenderItemSortKey sortKey, sf::Drawable* drawable, const char* string = "") : sortKey(sortKey), drawable(drawable), debugString(string) {}
    RenderItemSortKey sortKey{0};

    std::string debugString = "";
    sf::Drawable* drawable{nullptr};
};
