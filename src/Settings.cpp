/* Copyright 2014 <Piotr Derkowski> */

#include "Settings.hpp"

Settings Settings::getDefaultSettings() {
    Settings settings;

    settings.rows = 160;
    settings.columns = 80;
    settings.tileWidth = 96;
    settings.tileHeight = 48;

    return settings;
}
