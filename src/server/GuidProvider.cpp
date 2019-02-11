//
//  GuidProvider.cpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/11/19.
//

#include "GuidProvider.hpp"

GuidProvider::GuidProvider(uint64_t startGuid)
: _nextGuid(startGuid + 1)
{}

uint64_t GuidProvider::generateGuid()
{
    return _nextGuid++;
}
