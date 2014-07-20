/* Copyright 2014 <Piotr Derkowski> */

#include "terrains.hpp"
#include "TextureUtils.hpp"

const sf::VertexArray textures::terrains::hills = makeQuad(96, 48, sf::Vector2f(1, 197));
const sf::VertexArray textures::terrains::mountains = makeQuad(96, 48, sf::Vector2f(1, 197));
const sf::VertexArray textures::terrains::grassland = makeQuad(96, 48, sf::Vector2f(1, 99));
const sf::VertexArray textures::terrains::river = makeQuad(96, 48, sf::Vector2f(1, 99));
const sf::VertexArray textures::terrains::plains = makeQuad(96, 48, sf::Vector2f(1, 50));
const sf::VertexArray textures::terrains::forest = makeQuad(96, 48, sf::Vector2f(1, 50));
const sf::VertexArray textures::terrains::desert = makeQuad(96, 48, sf::Vector2f(1, 1));

const sf::VertexArray textures::terrains::visibleKnown = makeQuad(96, 48, sf::Vector2f(98, 50));
const sf::VertexArray textures::terrains::unvisibleKnown = makeQuad(96, 48, sf::Vector2f(98, 99));
const sf::VertexArray textures::terrains::unknown = makeQuad(96, 48, sf::Vector2f(98, 148));
