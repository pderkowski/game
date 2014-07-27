/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_MENUMODEL_HPP_
#define MENU_MENUMODEL_HPP_

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "MenuItem.hpp"


namespace menu {


class MenuModel {
public:
    typedef std::function<void()> Callback;
    void addItem(const std::string& itemName, Callback callback);

private:
    std::vector<std::shared_ptr<MenuItem>> items_;

    friend class MenuDrawer;
};


}  // namespace menu

#endif  // MENU_MENUMODEL_HPP_
