/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <utility>
#include <string>
#include <vector>
#include <functional>

class Menu {
public:
    void addItem(const std::string& itemName, std::function<void()> handler);

private:
    std::vector<std::pair<std::string, std::function<void()>>> items_;

    friend class MenuDrawer;
};

#endif  // MENU_HPP_
