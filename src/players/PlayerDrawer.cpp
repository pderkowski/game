/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include "SFML/Graphics.hpp"
#include "PlayerDrawer.hpp"
#include "units/Unit.hpp"
#include "MiscellaneousEnums.hpp"
#include "textures/TextureSet.hpp"
#include "textures/TextureSetFactory.hpp"
#include "Players.hpp"
#include "MapRenderer.hpp"
#include "Coordinates.hpp"
#include "Selection.hpp"
#include "Tile.hpp"


namespace players {


PlayerDrawer::PlayerDrawer(const Player* player, const MapRenderer* renderer)
    : player_(player),
    pathLayer_(textures::TextureSetFactory::getPathTextureSet()),
    selectionLayer_(textures::TextureSetFactory::getSelectionTextureSet()),
    unitLayer_(textures::TextureSetFactory::getUnitTextureSet()),
    fogLayer_(textures::TextureSetFactory::getFogTextureSet()),
    renderer_(renderer)
{
    updateUnitLayer(player_->players_->getVisibleUnits());
    updateFogLayer();
}

void PlayerDrawer::draw() const {
    MapRenderer::TargetProxy target = renderer_->getDynamicTarget();

    target.get()->draw(pathLayer_);
    target.get()->draw(selectionLayer_);
    target.get()->draw(unitLayer_);

    if (player_->isFogToggledOn_) {
        target.get()->draw(fogLayer_);
    }
}

void PlayerDrawer::updateUnitLayer(const std::vector<units::Unit>& visibleUnits) {
    unitLayer_.clear();

    for (const units::Unit& unit : visibleUnits) {
        auto tile = unit.getPosition();

        auto tilePosition = renderer_->getPosition(IntIsoPoint(tile.coords.toIsometric()));
        auto dualTilePosition = renderer_->getDualPosition(IntIsoPoint(tile.coords.toIsometric()));

        unitLayer_.add(unit, tilePosition);
        unitLayer_.add(unit, dualTilePosition);
    }
}

void PlayerDrawer::updateSelectionLayer() {
    selectionLayer_.clear();

    const Selection& selection = player_->selection_;
    if (selection.isSourceSelected()) {
        auto source = selection.getSource();

        auto sourcePosition = renderer_->getPosition(IntIsoPoint(source.coords.toIsometric()));
        auto sourceDualPosition = renderer_->getDualPosition(IntIsoPoint(source.coords.toIsometric()));

        selectionLayer_.add(miscellaneous::Type::Source, sourcePosition);
        selectionLayer_.add(miscellaneous::Type::Source, sourceDualPosition);
    }

    if (selection.isDestinationSelected()) {
        auto destination = selection.getDestination();

        auto destinationPosition = renderer_->getPosition(IntIsoPoint(destination.coords.toIsometric()));
        auto destinationDualPosition = renderer_->getDualPosition(IntIsoPoint(destination.coords.toIsometric()));

        selectionLayer_.add(miscellaneous::Type::Destination, destinationPosition);
        selectionLayer_.add(miscellaneous::Type::Destination, destinationDualPosition);
    }
}

void PlayerDrawer::updatePathLayer(const std::vector<Tile>& path) {
    pathLayer_.clear();

    for (size_t i = 0; i + 1 < path.size(); ++i) {
        const Tile& currentTile = path[i];
        const Tile& nextTile = path[i + 1];

        auto tilePosition = renderer_->getPosition(IntIsoPoint(currentTile.coords.toIsometric()));
        auto tileDualPosition = renderer_->getDualPosition(IntIsoPoint(currentTile.coords.toIsometric()));

        pathLayer_.add(currentTile.getDirection(nextTile), tilePosition);
        pathLayer_.add(currentTile.getDirection(nextTile), tileDualPosition);
    }
}

void PlayerDrawer::updateFogLayer() {
    fogLayer_.clear();

    const Fog& fog = player_->fog_;
    for (size_t r = 0; r < fog.getRowsNo(); ++r) {
        for (size_t c = 0; c < fog.getColumnsNo(); ++c) {
            auto position = renderer_->getPosition(IntIsoPoint(c, r));
            auto dualPosition = renderer_->getDualPosition(IntIsoPoint(c, r));

            fogLayer_.add(fog(r, c), position);
            fogLayer_.add(fog(r, c), dualPosition);
        }
    }
}

void PlayerDrawer::clearPathLayer() {
    pathLayer_.clear();
}

void PlayerDrawer::setPointer(const Player* player) {
    player_ = player;
}


}  // namespace players
