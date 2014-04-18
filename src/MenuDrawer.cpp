/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "MenuModel.hpp"
#include "MenuDrawer.hpp"
#include "Resources.hpp"

const float MenuDrawer::fontHeightFactor_ = 1.0 / 25;
const float MenuDrawer::lineSpacingFactor_ = fontHeightFactor_ / 4;

MenuDrawer::MenuDrawer(std::shared_ptr<MenuModel> model, Resources& resources)
        : model_(model), font_(resources.loadFont("fonts/UbuntuMono.ttf")) {
    resetItemDrawers();
}

void MenuDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    drawBackground(target, states);
    drawItems(target, states);
}

void MenuDrawer::drawBackground(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape menuBackground(sf::Vector2f(target.getSize().x, target.getSize().y));
    menuBackground.setFillColor(sf::Color(0, 0, 0, 190));

    const auto position = target.mapPixelToCoords(sf::Vector2i(0, 0));
    menuBackground.setPosition(position.x, position.y);

    target.draw(menuBackground, states);
}

void MenuDrawer::drawItems(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto itemDrawer : itemDrawers_) {
        target.draw(*itemDrawer, states);
    }
}

void MenuDrawer::resetItemDrawers() {
    itemDrawers_.clear();

    for (unsigned i = 0; i < model_->items_.size(); ++i) {
        float position = calculateItemPosition(i);

        itemDrawers_.push_back(std::make_shared<MenuItemDrawer>(
            model_->items_[i], fontHeightFactor_, position, font_));
    }
}

std::shared_ptr<MenuItem> MenuDrawer::getObjectByPosition(const sf::Vector2i& position,
        sf::RenderTarget& target) {
    for (auto itemDrawer : itemDrawers_) {
        auto object = itemDrawer->getObjectByPosition(position, target);
        if (object)
            return object;
    }

    return std::shared_ptr<MenuItem>();
}

float MenuDrawer::calculateItemPosition(int itemNo) const {
    const float center = 0.5;

    const float itemNoRelativeToCenter = itemNo - (model_->items_.size() - 1) / 2.0;

    return center + itemNoRelativeToCenter * (fontHeightFactor_ + lineSpacingFactor_);
}
