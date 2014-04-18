/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include <functional>
#include "MenuItem.hpp"

MenuItem::MenuItem(const std::string& itemName, std::function<void()> callback)
    : name_(itemName), callback_(callback)
{ }

std::string MenuItem::getName() const {
    return name_;
}

void MenuItem::execute() {
    callback_();
}
