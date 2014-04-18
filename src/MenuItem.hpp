/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENUITEM_HPP_
#define MENUITEM_HPP_

#include <string>
#include <functional>

class MenuItem {
public:
    MenuItem(const std::string& itemName, std::function<void()> callback);

    std::string getName() const;
    void execute();

private:
    std::string name_;
    std::function<void()> callback_;
};

#endif  // MENUITEM_HPP_
