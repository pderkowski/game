/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURESET_HPP_
#define TEXTURESET_HPP_

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Tile.hpp"
#include "TextureMatcher.hpp"

class TextureSet {
public:
    TextureSet(std::shared_ptr<const sf::Texture> texture);

    void add(Tile::Type type, const TextureMatcher& matcher);
    sf::VertexArray getVertices(std::shared_ptr<const Tile> tile,
        const std::vector<std::shared_ptr<const Tile>>& neighbors) const;
    bool contains(Tile::Type type) const;

    std::shared_ptr<const sf::Texture> getActualTexture() const;

private:
    std::shared_ptr<const sf::Texture> texture_;
    std::map<Tile::Type, TextureMatcher> textureMatchers_;
};

#endif  // TEXTURESET_HPP_
