/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "Menu.hpp"
#include "MenuDrawer.hpp"
#include "MenuModel.hpp"
#include "MenuItem.hpp"

Menu::Menu(Resources& resources)
    : model_(std::make_shared<MenuModel>()),
    drawer_(model_, resources),
    isVisible_(false)
{ }

void Menu::addItem(const std::string& itemName, Callback callback) {
    model_->addItem(itemName, callback);
    drawer_.resetItemDrawers();
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    drawer_.draw(target, states);
}

void Menu::handleClick(const sf::Event& e, sf::RenderTarget& target) {
    std::shared_ptr<MenuItem> clickedObject
        = drawer_.getObjectByPosition(sf::Vector2i(e.mouseButton.x, e.mouseButton.y), target);

    if (clickedObject) {
        clickedObject->execute();
    }
}

bool Menu::isVisible() const {
    return isVisible_;
}

void Menu::toggleVisibility() {
    isVisible_ = !isVisible_;
}
