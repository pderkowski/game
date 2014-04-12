/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include <map>
#include <string>
#include "boost/filesystem.hpp"
#include "SFML/Graphics.hpp"
#include "Resources.hpp"

Resources::Resources(const Paths& paths)
    : paths_(paths)
{ }

sf::Texture Resources::loadTexture(const std::string& relativePath) {
    boost::filesystem::path pathToTexture = paths_.getResourcePath(relativePath);

    if (loadedTextures_.find(pathToTexture) == loadedTextures_.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(pathToTexture.string())) {
            throw std::runtime_error("Could not load texture from " + pathToTexture.string());
        }

        loadedTextures_[pathToTexture] = texture;
    }

    return loadedTextures_.at(pathToTexture);
}

