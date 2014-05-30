/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURECOORDS_HPP_
#define TEXTURECOORDS_HPP_

#include <vector>
#include "SFML/Graphics.hpp"

template <class Key>
class TextureCoords {
public:
    void add(const Key& key, const std::vector<sf::Vector2f>& coords);
    std::vector<sf::Vector2f> get(const Key& key) const;
    bool contains(const Key& key) const;

private:
    std::map<Key, std::vector<sf::Vector2f>> texturePieces_;
};

template <class Key>
void TextureCoords<Key>::add(const Key& key, const std::vector<sf::Vector2f>& coords) {
    texturePieces_[key] = coords;
}

template <class Key>
std::vector<sf::Vector2f> TextureCoords<Key>::get(const Key& key) const {
    return texturePieces_.at(key);
}

template <class Key>
bool TextureCoords<Key>::contains(const Key& key) const {
    return texturePieces_.count(key);
}

#endif  // TEXTURECOORDS_HPP_
