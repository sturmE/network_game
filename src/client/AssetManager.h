//
//  AssetManager.h
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#pragma once

#include "SFMLTypes.h"
#include <map>
#include <string>

class AssetManager {
private:
    const std::string _assetDir;
    std::map<std::string, TexturePtr> _textures;
    TexturePtr _fallbackTexture { nullptr };
public:
    AssetManager(const std::string& assetDir);
    TexturePtr getOrCreateTexture(const std::string& name);
private:
    TexturePtr findTexture(const std::string& name);
    
};
