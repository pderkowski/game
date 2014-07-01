/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include "SFML/Graphics.hpp"
#include "Tile.hpp"
#include "TextureSet.hpp"
#include "Matcher.hpp"

TextureSet::TextureSet(std::shared_ptr<const sf::Texture> texture)
    : texture_(texture)
{ }

void TextureSet::add(std::shared_ptr<const Matcher> textureMatcher, const sf::VertexArray& vertices) {
    textureMatchers_.push_back(std::make_pair(textureMatcher, vertices));
}

sf::VertexArray TextureSet::getVertices(std::shared_ptr<const Tile> tile,
    const std::vector<std::shared_ptr<const Tile>>& neighbors) const
{
    sf::VertexArray matchedVertices;
    for (const auto& matcher_vertices : textureMatchers_) {
        if (matcher_vertices.first->match(tile, neighbors)) {
            for (unsigned i = 0; i < matcher_vertices.second.getVertexCount(); ++i) {
                matchedVertices.append(matcher_vertices.second[i]);
            }
        }
    }
    return matchedVertices;
}

std::shared_ptr<const sf::Texture> TextureSet::getActualTexture() const {
    return texture_;
}
