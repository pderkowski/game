/* Copyright 2014 <Piotr Derkowski> */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <memory>
#include "SFML/Graphics.hpp"
#include "TextureSet.hpp"

class Layer : public sf::Drawable {
public:
    explicit Layer(const TextureSet& textureSet);
    virtual ~Layer() { }

    virtual void draw(sf::RenderTarget& target,
        sf::RenderStates states = sf::RenderStates::Default) const;

    bool contains(Tile::Type type) const;
    void add(std::shared_ptr<const Tile> tile,
        const std::vector<std::shared_ptr<const Tile>>& neighbors,
        const sf::Vector2f& tileCenter);

private:
    TextureSet textureSet_;

    sf::VertexArray vertices_;
};

#endif  // LAYER_HPP_
