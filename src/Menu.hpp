/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "SFML/Graphics.hpp"
#include "MenuDrawer.hpp"
#include "MenuModel.hpp"

class Menu : public sf::Drawable {
public:
    typedef std::function<void()> Callback;

    explicit Menu(Resources& resources);
    virtual ~Menu() { }

    void addItem(const std::string& itemName, Callback callback);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void handleClick(const sf::Event& e, sf::RenderTarget& target);

    bool isVisible() const;
    void toggleVisibility();

private:
    std::shared_ptr<MenuModel> model_;
    MenuDrawer drawer_;

    bool isVisible_;
};

#endif  // MENU_HPP_
