/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <string>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Map.hpp"
#include "MapView.hpp"
#include "Game.hpp"
#include "MapGenerator.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    Paths paths(argv[0]);
    sf::Texture texture;
    auto pathToBasicTile = paths.getResourcePath("empty.png").string();
    if (!texture.loadFromFile(pathToBasicTile, sf::IntRect(10, 10, 16, 16))) {
        printf("FAIL!\n");
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    MapGenerator generator;
    auto map = std::make_shared<Map>(generator.generateMap(64, 64));

    MapView mapView(map, sprite);
    mapView.setOffset(sf::Vector2f(10, 10));

    Game game("game", map, mapView);
    game.start();

    return 0;
}
