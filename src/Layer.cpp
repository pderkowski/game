/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include <stdexcept>
#include "Layer.hpp"

Layer::Layer(std::shared_ptr<sf::Texture> texture)
    : texture_(texture),
    vertices_(sf::Quads)
{
    texture_->setSmooth(true);
}

void Layer::addVertices(const sf::VertexArray& vertices) {
    if (vertices.getPrimitiveType() != vertices_.getPrimitiveType()) {
        throw std::invalid_argument("Wrong primitive type of vertices being added to layer.");
    } else {
        for (unsigned i = 0; i < vertices.getVertexCount(); ++i) {
            vertices_.append(vertices[i]);
        }
    }
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = texture_.get();
    target.draw(vertices_, states);
}
