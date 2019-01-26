//
//  AssetManager.cpp
//  dirtyjam
//
//  Created by Eugene Sturm on 1/25/19.
//

#include "AssetManager.h"

AssetManager::AssetManager(const std::string& assetDir) : _assetDir(assetDir)
{
    _fallbackTexture.reset(new sf::Texture());
    _fallbackTexture->create(50, 50);
    std::vector<uint8_t> data(50*50*4);
    std::fill(begin(data), end(data), 255);
    _fallbackTexture->update(data.data());
}

TexturePtr AssetManager::getOrCreateTexture(const std::string& name)
{
    TexturePtr existingTexture = findTexture(name);
    if (existingTexture != nullptr) {
        return existingTexture;
    }
    
    std::string fullPath = _assetDir + name + ".png";
    
    TexturePtr texture(new sf::Texture);
    if (!texture->loadFromFile(fullPath)) {
        fprintf(stderr, "failed to load asset:%s path:%s", name.c_str(), fullPath.c_str());
        return _fallbackTexture;
    }
    
    _textures.emplace(name, texture);
    return _textures[name];
}

TexturePtr AssetManager::findTexture(const std::string& name)
{
    auto it = _textures.find(name);
    if (it == _textures.end()) {
        return nullptr;
    } else {
        return it->second;
    }
}
