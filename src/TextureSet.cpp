/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "SFML/Graphics.hpp"
#include "Tile.hpp"
#include "TextureSet.hpp"
#include "TextureMatcher.hpp"

TextureSet::TextureSet(std::shared_ptr<const sf::Texture> texture)
    : texture_(texture)
{ }

void TextureSet::add(Tile::Type type, const TextureMatcher& matcher) {
    textureMatchers_[type] = matcher;
}

sf::VertexArray TextureSet::getVertices(std::shared_ptr<const Tile> tile,
    const std::vector<std::shared_ptr<const Tile>>& neighbors) const
{
    return textureMatchers_.at(tile->type).match(neighbors);
}

bool TextureSet::contains(Tile::Type type) const {
    return textureMatchers_.count(type);
}

std::shared_ptr<const sf::Texture> TextureSet::getActualTexture() const {
    return texture_;
}
