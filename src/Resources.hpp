/* Copyright 2014 <Piotr Derkowski> */

#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include <map>
#include "boost/filesystem.hpp"
#include "SFML/Graphics.hpp"

class Resources {
public:
    static sf::Texture getTexture(const boost::filesystem::path& pathToResource);

private:
    static std::map<boost::filesystem::path, sf::Texture> loadedTextures_;
};

#endif  // RESOURCES_HPP_
