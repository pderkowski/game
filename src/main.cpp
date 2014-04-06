/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Map.hpp"
#include "MapView.hpp"
#include "Game.hpp"
#include "MapGenerator.hpp"
#include "Resources.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    Paths paths(argv[0]);
    auto map = std::make_shared<Map>(MapGenerator::generateMap(64, 64));

    std::map<Tile::Type, sf::Texture> tileTextures
        = { {Tile::Type::Empty, Resources::getTexture(paths.getResourcePath("tiles/empty.png"))},
            {Tile::Type::Water, Resources::getTexture(paths.getResourcePath("tiles/water.png"))},
            {Tile::Type::Hills, Resources::getTexture(paths.getResourcePath("tiles/hills.png"))},
            {Tile::Type::Plains, Resources::getTexture(paths.getResourcePath("tiles/plains.png"))},
            {Tile::Type::Mountains,
                Resources::getTexture(paths.getResourcePath("tiles/mountains.png"))} };
    MapView mapView(map, tileTextures);
    mapView.setOffset(sf::Vector2f(10, 10));

    Game game("game", map, mapView);
    game.start();

    return 0;
}
