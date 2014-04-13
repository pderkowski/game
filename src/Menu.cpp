/* Copyright 2014 <Piotr Derkowski> */

#include <functional>
#include <string>
#include <vector>
#include "Menu.hpp"

void Menu::addItem(const std::string& itemName, std::function<void()> handler) {
    items_.push_back(std::make_pair(itemName, handler));
}
