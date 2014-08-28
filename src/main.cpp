/* Copyright 2014 <Piotr Derkowski> */

#include <chrono>
#include "SFML/Graphics.hpp"
#include "global/Paths.hpp"
#include "global/Resources.hpp"
#include "global/Random.hpp"
#include "Game.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    global::Paths::initialize(argv[0]);
    global::Resources::initialize();
    global::Random::initialize(std::chrono::system_clock::now().time_since_epoch().count());

    Game game(160, 80);
    game.start();

    return 0;
}
