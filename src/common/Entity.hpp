//
//  Entity.hpp
//  dirtycommon
//
//  Created by Eugene Sturm on 2/5/19.
//

#pragma once

#include <stdint.h>

class Entity
{
private:
    const uint64_t _guid;
public:
    Entity(uint64_t guid);
    
    uint64_t guid() const { return _guid; }
};
