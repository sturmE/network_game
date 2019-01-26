//
//  RenderContext.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "RenderQueue.h"

struct RenderContext
{
    RenderQueue* renderQueue{nullptr};
    sf::View* view{nullptr};
};

