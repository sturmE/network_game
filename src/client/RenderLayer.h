//
//  RenderLayer.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

enum class RenderLayer : uint8_t
{
    World,
};

using RenderItemSortKey = uint32_t;

static RenderItemSortKey buildSortKey(RenderLayer renderLayer)
{
    return static_cast<std::underlying_type<RenderLayer>::type>(renderLayer);
}
