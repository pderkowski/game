/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURESET_HPP_
#define TEXTURESET_HPP_

#include <vector>
#include <memory>
#include <utility>
#include "SFML/Graphics.hpp"
#include "Tile.hpp"
#include "Matcher.hpp"

class TextureSet {
public:
    TextureSet(std::shared_ptr<const sf::Texture> texture);

    void add(std::shared_ptr<const Matcher> textureMatcher, const sf::VertexArray& vertices);
    sf::VertexArray getVertices(std::shared_ptr<const Tile> tile,
        const std::vector<std::shared_ptr<const Tile>>& neighbors) const;

    std::shared_ptr<const sf::Texture> getActualTexture() const;

private:
    std::shared_ptr<const sf::Texture> texture_;
    std::vector<std::pair<std::shared_ptr<const Matcher>, sf::VertexArray>> textureMatchers_;
};

#endif  // TEXTURESET_HPP_
