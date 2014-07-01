/* Copyright 2014 <Piotr Derkowski> */

#include "blends.hpp"
#include "TextureUtils.hpp"

const sf::VertexArray textures::blends::water_T = makeQuad(48, 24, sf::Vector2f(1, 1));
const sf::VertexArray textures::blends::water_R = makeQuad(48, 24, sf::Vector2f(50, 1), sf::Vector2f(48, 0));
const sf::VertexArray textures::blends::water_B = makeQuad(48, 24, sf::Vector2f(50, 26), sf::Vector2f(48, 24));
const sf::VertexArray textures::blends::water_L = makeQuad(48, 24, sf::Vector2f(1, 26), sf::Vector2f(0, 24));

const sf::VertexArray textures::blends::grassland_T = makeQuad(48, 24, sf::Vector2f(1, 51));
const sf::VertexArray textures::blends::grassland_R = makeQuad(48, 24, sf::Vector2f(50, 51), sf::Vector2f(48, 0));
const sf::VertexArray textures::blends::grassland_B = makeQuad(48, 24, sf::Vector2f(50, 76), sf::Vector2f(48, 24));
const sf::VertexArray textures::blends::grassland_L = makeQuad(48, 24, sf::Vector2f(1, 76), sf::Vector2f(0, 24));

const sf::VertexArray textures::blends::river_T = makeQuad(48, 24, sf::Vector2f(1, 51));
const sf::VertexArray textures::blends::river_R = makeQuad(48, 24, sf::Vector2f(50, 51), sf::Vector2f(48, 0));
const sf::VertexArray textures::blends::river_B = makeQuad(48, 24, sf::Vector2f(50, 76), sf::Vector2f(48, 24));
const sf::VertexArray textures::blends::river_L = makeQuad(48, 24, sf::Vector2f(1, 76), sf::Vector2f(0, 24));

const sf::VertexArray textures::blends::plains_T = makeQuad(48, 24, sf::Vector2f(1, 151));
const sf::VertexArray textures::blends::plains_R = makeQuad(48, 24, sf::Vector2f(50, 151), sf::Vector2f(48, 0));
const sf::VertexArray textures::blends::plains_B = makeQuad(48, 24, sf::Vector2f(50, 176), sf::Vector2f(48, 24));
const sf::VertexArray textures::blends::plains_L = makeQuad(48, 24, sf::Vector2f(1, 176), sf::Vector2f(0, 24));

const sf::VertexArray textures::blends::forest_T = makeQuad(48, 24, sf::Vector2f(1, 151));
const sf::VertexArray textures::blends::forest_R = makeQuad(48, 24, sf::Vector2f(50, 151), sf::Vector2f(48, 0));
const sf::VertexArray textures::blends::forest_B = makeQuad(48, 24, sf::Vector2f(50, 176), sf::Vector2f(48, 24));
const sf::VertexArray textures::blends::forest_L = makeQuad(48, 24, sf::Vector2f(1, 176), sf::Vector2f(0, 24));

const sf::VertexArray textures::blends::desert_T = makeQuad(48, 24, sf::Vector2f(99, 1));
const sf::VertexArray textures::blends::desert_R = makeQuad(48, 24, sf::Vector2f(148, 1), sf::Vector2f(48, 0));
const sf::VertexArray textures::blends::desert_B = makeQuad(48, 24, sf::Vector2f(148, 26), sf::Vector2f(48, 24));
const sf::VertexArray textures::blends::desert_L = makeQuad(48, 24, sf::Vector2f(99, 26), sf::Vector2f(0, 24));

const sf::VertexArray textures::blends::hills_T = makeQuad(48, 24, sf::Vector2f(1, 101));
const sf::VertexArray textures::blends::hills_R = makeQuad(48, 24, sf::Vector2f(50, 101), sf::Vector2f(48, 0));
const sf::VertexArray textures::blends::hills_B = makeQuad(48, 24, sf::Vector2f(50, 126), sf::Vector2f(48, 24));
const sf::VertexArray textures::blends::hills_L = makeQuad(48, 24, sf::Vector2f(1, 126), sf::Vector2f(0, 24));

const sf::VertexArray textures::blends::mountains_T = hills_T;
const sf::VertexArray textures::blends::mountains_R = hills_R;
const sf::VertexArray textures::blends::mountains_B = hills_B;
const sf::VertexArray textures::blends::mountains_L = hills_L;
