/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Grid.hpp"
#include "Game.hpp"

std::string resourceDirectory = "../rsc/";

int main(__attribute__((unused)) int argc, char* argv[]) {
    Paths paths(argv[0]);

    sf::Texture texture;
    auto pathToBasicTile = paths.getResourcePath("basic_tile.png").string();
    if (!texture.loadFromFile(pathToBasicTile, sf::IntRect(10, 10, 16, 16))) {
        printf("FAIL!\n");
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    Grid grid(32, 32, sprite);
    grid.setOffset(sf::Vector2f(10, 10));

    Game game("game", grid);
    game.start();

    return 0;
}
