/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics/Color.hpp"
#include "Renderer.hpp"
#include "Interface.hpp"
#include "Layout.hpp"
#include "UnitFrame.hpp"
#include "players/Player.hpp"
#include "GameNotification.hpp"
class Settings;
namespace map { class MapModel; }


namespace interface {


Interface::Interface(const Settings& settings, const Renderer* renderer)
    : layout_(renderer), minimapFrame_(settings, renderer), unitFrame_(renderer)
{
    minimapFrame_.setPosition(layout_.addSlot(minimapFrame_.getSize()));
    unitFrame_.setPosition(layout_.addSlot(unitFrame_.getSize(), sf::Color(255, 255, 255, 127)));
}

void Interface::draw() const {
    layout_.draw();
    minimapFrame_.draw();
    unitFrame_.draw();
}

void Interface::updateMinimapBackground(const map::MapModel* map, const players::Player* player) {
    minimapFrame_.updateBackground(*map, *player);
}

void Interface::updateSelectedUnitFrame(const players::Player* player) {
    if (player->isUnitSelected()) {
        unitFrame_.setUnitDisplayed(player->getSelectedUnit());
    } else {
        unitFrame_.clear();
    }
}

void Interface::onNotify(const RendererNotification& ntion) {
    minimapFrame_.updateDisplayedRectangle(ntion.displayedRectangle);
}

void Interface::onNotify(const GameNotification& ntion) {
    typedef GameNotification GN;

    switch (ntion.type) {
    case GN::NewMapGenerated: case GN::PlayerSwitched: case GN::UnitAdded:
    case GN::SecondarySelectionSet:
        updateMinimapBackground(ntion.map, ntion.player);
        updateSelectedUnitFrame(ntion.player);
        break;
    case GN::FogToggled:
        updateMinimapBackground(ntion.map, ntion.player);
        break;
    case GN::UnitRemoved: case GN::PrimarySelectionSet:
        updateSelectedUnitFrame(ntion.player);
        break;
    default:
        break;
    }
}


}  // namespace interface
