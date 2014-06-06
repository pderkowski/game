/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include <stdexcept>
#include "Layer.hpp"

Layer::Layer(const TextureSet& textureSet)
    : textureSet_(textureSet),
    vertices_(sf::Quads)
{ }

bool Layer::contains(Tile::Type type) const {
    return textureSet_.contains(type);
}

void Layer::add(std::shared_ptr<const Tile> tile,
    const std::vector<std::shared_ptr<const Tile>>& neighbors,
    const sf::Vector2f& position)
{
    auto vertices = textureSet_.getVertices(tile, neighbors);

    for (unsigned i = 0; i < vertices.getVertexCount(); ++i) {
        vertices[i].position += (position - sf::Vector2f(48, 24));
        vertices_.append(vertices[i]);
    }
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = textureSet_.getActualTexture().get();
    target.draw(vertices_, states);
}
