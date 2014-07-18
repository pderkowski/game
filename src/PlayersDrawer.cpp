/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include "SFML/Graphics.hpp"
#include "PlayersDrawer.hpp"
#include "units/Unit.hpp"
#include "MiscellaneousEnums.hpp"
#include "TextureSet.hpp"
#include "TextureSetFactory.hpp"
#include "Players.hpp"
#include "MapRenderer.hpp"
#include "Coordinates.hpp"
#include "Selection.hpp"
#include "Tile.hpp"

PlayersDrawer::PlayersDrawer(const Players* players, const MapRenderer* renderer)
    : players_(players),
    pathLayer_(TextureSetFactory::getPathTextureSet()),
    selectionLayer_(TextureSetFactory::getSelectionTextureSet()),
    unitLayer_(TextureSetFactory::getUnitTextureSet()),
    renderer_(renderer)
{ }

void PlayersDrawer::draw() const {
    auto target = renderer_->getDynamicView();
    target->draw(pathLayer_);
    target->draw(selectionLayer_);
    target->draw(unitLayer_);
}

void PlayersDrawer::updateUnitLayer() {
    unitLayer_.clear();

    for (const units::Unit* unit : players_->getAllUnits()) {
        auto tile = unit->getPosition();

        auto tilePosition = renderer_->getPosition(IntIsoPoint(tile->coords.toIsometric()));
        auto dualTilePosition = renderer_->getDualPosition(IntIsoPoint(tile->coords.toIsometric()));

        unitLayer_.add(*unit, tilePosition);
        unitLayer_.add(*unit, dualTilePosition);
    }
}

void PlayersDrawer::updateSelectionLayer(const Selection& selection) {
    selectionLayer_.clear();

    if (selection.isSourceSelected()) {
        auto source = selection.getSource();

        auto sourcePosition = renderer_->getPosition(IntIsoPoint(source->coords.toIsometric()));
        auto sourceDualPosition = renderer_->getDualPosition(IntIsoPoint(source->coords.toIsometric()));

        selectionLayer_.add(miscellaneous::Type::Source, sourcePosition);
        selectionLayer_.add(miscellaneous::Type::Source, sourceDualPosition);
    }

    if (selection.isDestinationSelected()) {
        auto destination = selection.getDestination();

        auto destinationPosition = renderer_->getPosition(IntIsoPoint(destination->coords.toIsometric()));
        auto destinationDualPosition = renderer_->getDualPosition(IntIsoPoint(destination->coords.toIsometric()));

        selectionLayer_.add(miscellaneous::Type::Destination, destinationPosition);
        selectionLayer_.add(miscellaneous::Type::Destination, destinationDualPosition);
    }
}

void PlayersDrawer::updatePathLayer(const std::vector<Tile>& path) {
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
