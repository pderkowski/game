/* Copyright 2014 <Piotr Derkowski> */

#include <chrono>
#include "global/Paths.hpp"
#include "global/Resources.hpp"
#include "global/Random.hpp"
#include "Application.hpp"
#include "Settings.hpp"

int main(__attribute__((unused)) int argc, char* argv[]) {
    global::Paths::initialize(argv[0]);
    global::Resources::initialize();
    global::Random::initialize(std::chrono::system_clock::now().time_since_epoch().count());

    Application app(Settings::getDefaultSettings());
    app.run();

    return 0;
}
