//
//  GuidProvider.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/11/19.
//

#pragma once

#include <stdint.h>

class GuidProvider
{
private:
    uint64_t _nextGuid { 0 };
public:
    GuidProvider(uint64_t startGuid = 1);
    
    uint64_t generateGuid();
};
