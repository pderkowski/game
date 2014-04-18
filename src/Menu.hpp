/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "MenuItem.hpp"

class Menu {
public:
    typedef std::function<void()> Callback;
    void addItem(const std::string& itemName, Callback callback);

private:
    std::vector<std::shared_ptr<MenuItem>> items_;

    friend class MenuDrawer;
};

#endif  // MENU_HPP_
