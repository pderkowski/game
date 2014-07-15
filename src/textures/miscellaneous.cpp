/* Copyright 2014 <Piotr Derkowski> */

#include "miscellaneous.hpp"
#include "TextureUtils.hpp"

const sf::VertexArray textures::miscellaneous::source = makeQuad(96, 48, sf::Vector2f(1, 1));
const sf::VertexArray textures::miscellaneous::destination = source;
const sf::VertexArray textures::miscellaneous::bottomRight = makeQuad(96, 48, sf::Vector2f(1, 50), sf::Vector2f(48, 0));
const sf::VertexArray textures::miscellaneous::topLeft = makeQuad(96, 48, sf::Vector2f(1, 50), sf::Vector2f(-48, 0));
const sf::VertexArray textures::miscellaneous::topRight = makeQuad(96, 48, sf::Vector2f(98, 50), sf::Vector2f(0, -24));
const sf::VertexArray textures::miscellaneous::bottomLeft = makeQuad(96, 48, sf::Vector2f(98, 50), sf::Vector2f(0, 24));
const sf::VertexArray textures::miscellaneous::top = makeQuad(96, 48, sf::Vector2f(195, 50), sf::Vector2f(-24, -12));
const sf::VertexArray textures::miscellaneous::bottom = makeQuad(96, 48, sf::Vector2f(195, 50), sf::Vector2f(24, 12));
const sf::VertexArray textures::miscellaneous::left = makeQuad(96, 48, sf::Vector2f(292, 50), sf::Vector2f(-24, 12));
const sf::VertexArray textures::miscellaneous::right = makeQuad(96, 48, sf::Vector2f(292, 50), sf::Vector2f(24, -12));
