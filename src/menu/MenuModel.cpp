/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include <string>
#include <vector>
#include "MenuModel.hpp"
#include "MenuItem.hpp"


namespace menu {


void MenuModel::addItem(const std::string& itemName, Callback callback) {
    items_.push_back(std::make_shared<MenuItem>(itemName, callback));
}


}  // namespace menu
