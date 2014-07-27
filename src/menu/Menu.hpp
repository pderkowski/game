/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_MENU_HPP_
#define MENU_MENU_HPP_

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "SFML/Graphics.hpp"
#include "MenuDrawer.hpp"
#include "MenuModel.hpp"


namespace menu {


class Menu {
public:
    typedef std::function<void()> Callback;

    Menu(std::shared_ptr<sf::RenderWindow>);
    virtual ~Menu() { }

    void addItem(const std::string& itemName, Callback callback);
    virtual void draw() const;
    void handleLeftClick(const sf::Event& e);
    void handleMouseMoved(const sf::Event& e);

    bool isVisible() const;
    void toggleVisibility();

private:
    std::shared_ptr<MenuModel> model_;
    MenuDrawer drawer_;

    bool isVisible_;
};


}  // namespace menu


#endif  // MENU_MENU_HPP_
