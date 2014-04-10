/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include <map>
#include <string>
#include "boost/filesystem.hpp"
#include "SFML/Graphics.hpp"
#include "Resources.hpp"
#include "Tile.hpp"

Resources::Resources(const Paths& paths)
        : paths_(paths), loadedTextures_() {
    loadResources();
}

std::map<Tile::Type, sf::Texture> Resources::getTileTextures() const {
    return loadedTextures_;
}

void Resources::loadResources() {
    loadTileTexture(Tile::Type::Empty, paths_.getResourcePath("tiles/empty.png"));
    loadTileTexture(Tile::Type::Water, paths_.getResourcePath("tiles/water.png"));
    loadTileTexture(Tile::Type::Hills, paths_.getResourcePath("tiles/hills.png"));
    loadTileTexture(Tile::Type::Plains, paths_.getResourcePath("tiles/plains.png"));
    loadTileTexture(Tile::Type::Mountains, paths_.getResourcePath("tiles/mountains.png"));
}

void Resources::loadTileTexture(const Tile::Type alias,
        const boost::filesystem::path& pathToTexture) {
    if (loadedTextures_.find(alias) == loadedTextures_.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(pathToTexture.string())) {
            throw std::runtime_error("Could not load texture from " + pathToTexture.string());
        }

        loadedTextures_[alias] = texture;
    }
}
