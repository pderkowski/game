/* Copyright 2014 <Piotr Derkowski> */

#ifndef GLOBAL_RESOURCES_HPP_
#define GLOBAL_RESOURCES_HPP_

#include <map>
#include <string>
#include <memory>
#include "boost/filesystem.hpp"
#include "SFML/Graphics.hpp"
#include "Paths.hpp"


namespace global {


class Resources {
public:
    static void initialize();

    static std::shared_ptr<const sf::Texture> loadTexture(const std::string& relativePath);
    static sf::Font loadFont(const std::string& relativePath);
    static sf::Image loadImage(const std::string& relativePath);

private:
    Resources() = delete;

    static std::map<boost::filesystem::path, std::shared_ptr<sf::Texture>> loadedTextures_;
    static std::map<boost::filesystem::path, sf::Font> loadedFonts_;
    static std::map<boost::filesystem::path, sf::Image> loadedImages_;
};


}  // namespace global

#endif  // GLOBAL_RESOURCES_HPP_
