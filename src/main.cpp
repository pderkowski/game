/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Grid.hpp"

std::string resourceDirectory = "../rsc/";

int main(__attribute__((unused)) int argc, char* argv[]) {
    Paths paths(argv[0]);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

    sf::Texture texture;
    auto pathToBasicTile = paths.getResourcePath("basic_tile.png").string();
    if (!texture.loadFromFile(pathToBasicTile, sf::IntRect(10, 10, 16, 16))) {
        printf("FAIL!\n");
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Vector2f offset(10, 10);
    sprite.move(offset);

    Grid grid(32, 32, sprite);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(grid);
        window.display();
    }

    return 0;
}
