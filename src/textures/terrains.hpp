/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURES_TERRAINS_HPP_
#define TEXTURES_TERRAINS_HPP_

#include "SFML/Graphics.hpp"

namespace textures {

namespace terrains {

extern const sf::VertexArray hills;
extern const sf::VertexArray mountains;
extern const sf::VertexArray grassland;
extern const sf::VertexArray river;
extern const sf::VertexArray plains;
extern const sf::VertexArray forest;
extern const sf::VertexArray desert;

extern const sf::VertexArray visibleKnown;
extern const sf::VertexArray unvisibleKnown;
extern const sf::VertexArray unknown;

}  // terrains

}  // textures

#endif  // TEXTURES_TERRAINS_HPP_
