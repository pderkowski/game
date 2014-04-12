/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Map.hpp"
#include "Game.hpp"
#include "MapGenerator.hpp"
#include "Resources.hpp"
#include "Menu.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    Resources resources(Paths{argv[0]}); // NOLINT

    auto map = std::make_shared<Map>(MapGenerator::generateMap(100, 160));
    auto menu = std::make_shared<Menu>(Menu());

    Game game("game", map, menu, resources);
    game.start();

    return 0;
}
