/* Copyright 2014 <Piotr Derkowski> */

#include <chrono>
#include "SFML/Graphics.hpp"
#include "Paths.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "Random.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    Resources::initialize(Paths{argv[0]});
    Random::initialize(std::chrono::system_clock::now().time_since_epoch().count());

    Game game(160, 80);
    game.start();

    return 0;
}
