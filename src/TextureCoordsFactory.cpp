/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "SFML/Graphics.hpp"
#include "TextureCoords.hpp"
#include "Tile.hpp"
#include "TextureCoordsFactory.hpp"

namespace {

std::vector<sf::Vector2f> makeRectangle(const sf::Vector2f& topLeft, float width, float height) {
    std::vector<sf::Vector2f> rectangle;
    rectangle.push_back(topLeft);
    rectangle.push_back(sf::Vector2f(topLeft.x + width, topLeft.y));
    rectangle.push_back(sf::Vector2f(topLeft.x + width, topLeft.y + height));
    rectangle.push_back(sf::Vector2f(topLeft.x, topLeft.y + height));
    return rectangle;
}

}


TextureCoords<Tile::Type> TextureCoordsFactory::getTerrainTextureCoords() {
    TextureCoords<Tile::Type> tc;
    tc.add(Tile::Type::Hills, ::makeRectangle(sf::Vector2f(1, 197), 96, 48));
    tc.add(Tile::Type::Mountains, ::makeRectangle(sf::Vector2f(1, 246), 96, 48));
    tc.add(Tile::Type::Plains, ::makeRectangle(sf::Vector2f(1, 99), 96, 48));
    tc.add(Tile::Type::Water, ::makeRectangle(sf::Vector2f(98, 1), 96, 48));
    return tc;
}
