/* Copyright 2014 <Piotr Derkowski> */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include "SFML/Graphics.hpp"

class Layer : public sf::Drawable {
public:
    explicit Layer(const sf::Texture& texture);
    virtual ~Layer() { }

    virtual void draw(sf::RenderTarget& target,
        sf::RenderStates states = sf::RenderStates::Default) const;

    void addVertices(const sf::VertexArray& vertices);

private:
    sf::Texture texture_;

    sf::VertexArray vertices_;
};

#endif  // LAYER_HPP_
