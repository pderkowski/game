/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include <utility>
#include <map>
#include <string>
#include "boost/filesystem.hpp"
#include "SFML/Graphics.hpp"
#include "Resources.hpp"

std::map<boost::filesystem::path, sf::Texture> Resources::loadedTextures_;

sf::Texture Resources::getTexture(const boost::filesystem::path& pathToResource) {
    if (loadedTextures_.find(pathToResource) == loadedTextures_.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(pathToResource.string())) {
            throw std::runtime_error("Could not load texture from " + pathToResource.string());
        }

        loadedTextures_.insert(std::make_pair(pathToResource, texture));
    }

    return loadedTextures_.at(pathToResource);
}
