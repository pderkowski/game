/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_MENUITEM_HPP_
#define MENU_MENUITEM_HPP_

#include <string>
#include <functional>


namespace menu {


class MenuItem {
public:
    MenuItem(const std::string& itemName, std::function<void()> callback);

    std::string getName() const;
    void execute();

private:
    std::string name_;
    std::function<void()> callback_;
};


}  // namespace menu


#endif  // MENU_MENUITEM_HPP_
