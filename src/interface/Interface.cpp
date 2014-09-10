/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "Renderer.hpp"
#include "Interface.hpp"
#include "Layout.hpp"
#include "UnitFrame.hpp"
#include "players/Players.hpp"


namespace interface {


Interface::Interface(const map::MapModel* model, const players::Players* players,
    const Renderer* renderer)
        : model_(model),
        players_(players),
        layout_(renderer),
        minimapFrame_(*model, renderer),
        unitFrame_(renderer)
{
    minimapFrame_.setPosition(layout_.addSlot(minimapFrame_.getSize()));
    unitFrame_.setPosition(layout_.addSlot(unitFrame_.getSize(), sf::Color(255, 255, 255, 127)));

    updateEverything();
}

void Interface::setModel(const map::MapModel* model) {
    model_ = model;

    updateEverything();
}

void Interface::draw() const {
    layout_.draw();
    minimapFrame_.draw();
    unitFrame_.draw();
}

void Interface::updateEverything() {
    updateMinimapBackground();
    updateMinimapDisplayedRectangle();
    updateSelectedUnitFrame();
}

void Interface::updateMinimapBackground() {
    minimapFrame_.updateBackground(*model_, *(players_->getCurrentPlayer()));
}

void Interface::updateMinimapDisplayedRectangle() {
    minimapFrame_.updateDisplayedRectangle();
}

void Interface::updateSelectedUnitFrame() {
    if (players_->isUnitSelected()) {
        unitFrame_.setUnitDisplayed(players_->getSelectedUnit());
    } else {
        unitFrame_.clear();
    }
}


}  // namespace interface
