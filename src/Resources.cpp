/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include <map>
#include <string>
#include "boost/filesystem.hpp"
#include "SFML/Graphics.hpp"
#include "Resources.hpp"

// Static variables
Paths Resources::paths_;
std::map<boost::filesystem::path, sf::Texture> Resources::loadedTextures_;
std::map<boost::filesystem::path, sf::Font> Resources::loadedFonts_;
std::map<boost::filesystem::path, sf::Image> Resources::loadedImages_;


void Resources::initialize(const Paths& paths)
{
    paths_ = paths;
}

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

sf::Font Resources::loadFont(const std::string& relativePath) {
    boost::filesystem::path pathToFont = paths_.getResourcePath(relativePath);

    if (loadedFonts_.find(pathToFont) == loadedFonts_.end()) {
        sf::Font font;
        if (!font.loadFromFile(pathToFont.string())) {
            throw std::runtime_error("Could not load font from " + pathToFont.string());
        }

        loadedFonts_[pathToFont] = font;
    }

    return loadedFonts_.at(pathToFont);
}

sf::Image Resources::loadImage(const std::string& relativePath) {
    boost::filesystem::path pathToImage = paths_.getResourcePath(relativePath);

    if (loadedImages_.find(pathToImage) == loadedImages_.end()) {
        sf::Image image;
        if (!image.loadFromFile(pathToImage.string())) {
            throw std::runtime_error("Could not load image from " + pathToImage.string());
        }

        loadedImages_[pathToImage] = image;
    }

    return loadedImages_.at(pathToImage);
}
