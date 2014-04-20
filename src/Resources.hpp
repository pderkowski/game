/* Copyright 2014 <Piotr Derkowski> */

#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include <map>
#include <string>
#include "boost/filesystem.hpp"
#include "SFML/Graphics.hpp"
#include "Paths.hpp"

class Resources {
public:
    explicit Resources(const Paths& paths);
    sf::Texture loadTexture(const std::string& relativePath);
    sf::Font loadFont(const std::string& relativePath);
    sf::Image loadImage(const std::string& relativePath);

private:
    Paths paths_;
    std::map<boost::filesystem::path, sf::Texture> loadedTextures_;
    std::map<boost::filesystem::path, sf::Font> loadedFonts_;
    std::map<boost::filesystem::path, sf::Image> loadedImages_;
};

#endif  // RESOURCES_HPP_
