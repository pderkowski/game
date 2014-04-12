/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Map.hpp"
#include "MapDrawer.hpp"
#include "Game.hpp"
#include "MapGenerator.hpp"
#include "Resources.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    Resources resources(Paths{argv[0]}); // NOLINT

    auto map = std::make_shared<Map>(MapGenerator::generateMap(100, 160));

    MapDrawer mapDrawer(map, resources.getTileTextures());
    mapDrawer.setOffset(sf::Vector2f(10, 10));

    Game game("game", map, mapDrawer);
    game.start();

    return 0;
}
