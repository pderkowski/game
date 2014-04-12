/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <string>
#include <map>
#include <functional>

class Menu {
public:
    void addItem(const std::string& itemName, std::function<void()> handler);

private:
    std::map<std::string, std::function<void()>> handlers_;
};

#endif  // MENU_HPP_
