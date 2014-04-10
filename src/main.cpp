/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Map.hpp"
#include "MapView.hpp"
#include "Game.hpp"
#include "MapGenerator.hpp"
#include "Resources.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    Resources resources(Paths{argv[0]}); // NOLINT

    auto map = std::make_shared<Map>(MapGenerator::generateMap(100, 140));

    MapView mapView(map, resources.getTileTextures());
    mapView.setOffset(sf::Vector2f(10, 10));

    Game game("game", map, mapView);
    game.start();

    return 0;
}
