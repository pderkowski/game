/* Copyright 2014 <Piotr Derkowski> */

#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include <map>
#include "boost/filesystem.hpp"
#include "SFML/Graphics.hpp"
#include "Tile.hpp"
#include "Paths.hpp"

class Resources {
public:
    explicit Resources(const Paths& paths);
    std::map<Tile::Type, sf::Texture> getTileTextures() const;

private:
    void loadResources();
    void loadTileTexture(const Tile::Type alias,
        const boost::filesystem::path& pathToTexture);

    Paths paths_;
    std::map<Tile::Type, sf::Texture> loadedTextures_;
};

#endif  // RESOURCES_HPP_
