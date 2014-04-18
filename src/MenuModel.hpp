/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENUMODEL_HPP_
#define MENUMODEL_HPP_

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "MenuItem.hpp"

class MenuModel {
public:
    typedef std::function<void()> Callback;
    void addItem(const std::string& itemName, Callback callback);

private:
    std::vector<std::shared_ptr<MenuItem>> items_;

    friend class MenuDrawer;
};

#endif  // MENUMODEL_HPP_
