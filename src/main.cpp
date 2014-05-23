/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Game.hpp"
#include "Resources.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    Resources resources(Paths{argv[0]});

    Game game(200, 100, resources);
    game.start();

    return 0;
}
