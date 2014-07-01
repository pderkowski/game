/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURES_TEXTUREUTILS_HPP_
#define TEXTURES_TEXTUREUTILS_HPP_

#include "SFML/Graphics.hpp"

namespace textures {

inline sf::VertexArray makeQuad(float width, float height, const sf::Vector2f& texCoords,
    const sf::Vector2f& position = sf::Vector2f(0, 0))
{
    sf::VertexArray rectangle(sf::Quads, 4);
    rectangle[0].position = position + sf::Vector2f(0, 0);
    rectangle[1].position = position + sf::Vector2f(width, 0);
    rectangle[2].position = position + sf::Vector2f(width, height);
    rectangle[3].position = position + sf::Vector2f(0, height);

    rectangle[0].texCoords = texCoords + sf::Vector2f(0, 0);
    rectangle[1].texCoords = texCoords + sf::Vector2f(width, 0);
    rectangle[2].texCoords = texCoords + sf::Vector2f(width, height);
    rectangle[3].texCoords = texCoords + sf::Vector2f(0, height);

    return rectangle;
}

}  // textures

#endif  // TEXTURES_TEXTUREUTILS_HPP_
