//
//  WorldServices.hpp
//  dirtyserver
//
//  Created by Eugene Sturm on 2/5/19.
//

#pragma once

class CharacterDatabase;

class WorldServices
{
private:
    CharacterDatabase* _charDb { nullptr };
public:
    WorldServices() {}
    
    CharacterDatabase* characterDatabase() { return _charDb; }
private:
    void setCharacterDatabase(CharacterDatabase* charDb) { _charDb = charDb; }
    friend class World;
};
