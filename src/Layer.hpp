/* Copyright 2014 <Piotr Derkowski> */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <memory>
#include "SFML/Graphics.hpp"

class Layer : public sf::Drawable {
public:
    explicit Layer(std::shared_ptr<sf::Texture> texture);
    virtual ~Layer() { }

    virtual void draw(sf::RenderTarget& target,
        sf::RenderStates states = sf::RenderStates::Default) const;

    void addVertices(const sf::VertexArray& vertices);

private:
    std::shared_ptr<sf::Texture> texture_;

    sf::VertexArray vertices_;
};

#endif  // LAYER_HPP_
