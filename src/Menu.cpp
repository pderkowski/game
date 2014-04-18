/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include <string>
#include <vector>
#include "Menu.hpp"
#include "MenuItem.hpp"

void Menu::addItem(const std::string& itemName, Callback callback) {
    items_.push_back(std::make_shared<MenuItem>(itemName, callback));
}
