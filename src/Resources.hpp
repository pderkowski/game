/* Copyright 2014 <Piotr Derkowski> */

#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include <map>
#include <string>
#include <memory>
#include "boost/filesystem.hpp"
#include "SFML/Graphics.hpp"
#include "Paths.hpp"

class Resources {
public:
    static void initialize(const Paths& paths);
    static std::shared_ptr<sf::Texture> loadTexture(const std::string& relativePath);
    static sf::Font loadFont(const std::string& relativePath);
    static sf::Image loadImage(const std::string& relativePath);

private:
    Resources() = delete;

    static Paths paths_;
    static std::map<boost::filesystem::path, std::shared_ptr<sf::Texture>> loadedTextures_;
    static std::map<boost::filesystem::path, sf::Font> loadedFonts_;
    static std::map<boost::filesystem::path, sf::Image> loadedImages_;
};

#endif  // RESOURCES_HPP_
