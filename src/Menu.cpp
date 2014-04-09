/* Copyright 2014 <Piotr Derkowski> */

#include "Menu.hpp"

Menu::Menu(float width, float height)
    : width_(width), height_(height)
{ }

float Menu::width() const {
    return width_;
}

float Menu::height() const {
    return height_;
}
