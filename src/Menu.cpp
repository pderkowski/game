/* Copyright 2014 <Piotr Derkowski> */

#include <functional>
#include <string>
#include <map>
#include "Menu.hpp"

void Menu::addItem(const std::string& itemName, std::function<void()> handler) {
    handlers_[itemName] = handler;
}
