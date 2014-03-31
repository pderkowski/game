/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <string>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Board.hpp"
#include "BoardView.hpp"
#include "Game.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    Paths paths(argv[0]);

    sf::Texture texture;
    auto pathToBasicTile = paths.getResourcePath("empty.png").string();
    if (!texture.loadFromFile(pathToBasicTile, sf::IntRect(10, 10, 16, 16))) {
        printf("FAIL!\n");
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    auto board = std::make_shared<Board>(64, 64);

    BoardView boardView(board, sprite);
    boardView.setOffset(sf::Vector2f(10, 10));

    Game game("game", board, boardView);
    game.start();

    return 0;
}
