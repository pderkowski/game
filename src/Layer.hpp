/* Copyright 2014 <Piotr Derkowski> */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <memory>
#include "SFML/Graphics.hpp"
#include "TextureSet.hpp"
#include "Tile.hpp"

class Layer : public sf::Drawable {
public:
    explicit Layer(const TextureSet& textureSet);
    virtual ~Layer() { }

    virtual void draw(sf::RenderTarget& target,
        sf::RenderStates states = sf::RenderStates::Default) const;

    virtual void add(std::shared_ptr<const Tile> tile, const sf::Vector2f& tileCenter);

protected:
    TextureSet textureSet_;

    sf::VertexArray vertices_;
};

#endif  // LAYER_HPP_
