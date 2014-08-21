/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include "SFML/Graphics.hpp"
#include "PlayersDrawer.hpp"
#include "units/Unit.hpp"
#include "MiscellaneousEnums.hpp"
#include "textures/TextureSet.hpp"
#include "textures/TextureSetFactory.hpp"
#include "MapRenderer.hpp"
#include "Coordinates.hpp"
#include "Selection.hpp"
#include "Tile.hpp"


namespace players {


PlayersDrawer::PlayersDrawer(const MapRenderer* renderer)
    : pathLayer_(textures::TextureSetFactory::getPathTextureSet()),
    selectionLayer_(textures::TextureSetFactory::getSelectionTextureSet()),
    unitLayer_(textures::TextureSetFactory::getUnitTextureSet()),
    fogLayer_(textures::TextureSetFactory::getFogTextureSet()),
    renderer_(renderer)
{ }

void PlayersDrawer::draw() const {
    MapRenderer::TargetProxy target = renderer_->getDynamicTarget();

    target.get()->draw(pathLayer_);
    target.get()->draw(selectionLayer_);
    target.get()->draw(unitLayer_);
    target.get()->draw(fogLayer_);
}

void PlayersDrawer::updateUnitLayer(const std::vector<units::Unit>& visibleUnits) {
    unitLayer_.clear();

    for (const units::Unit& unit : visibleUnits) {
        auto tile = unit.getPosition();

        auto tilePosition = renderer_->getPosition(IntIsoPoint(tile.coords.toIsometric()));
        auto dualTilePosition = renderer_->getDualPosition(IntIsoPoint(tile.coords.toIsometric()));

        unitLayer_.add(unit, tilePosition);
        unitLayer_.add(unit, dualTilePosition);
    }
}

void PlayersDrawer::updateSelectionLayer(const Selection& selection) {
    selectionLayer_.clear();

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

void PlayersDrawer::updatePathLayer(const Selection& selection) {
    pathLayer_.clear();

    auto path = selection.getPath();
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        const Tile& currentTile = path[i];
        const Tile& nextTile = path[i + 1];

        auto tilePosition = renderer_->getPosition(IntIsoPoint(currentTile.coords.toIsometric()));
        auto tileDualPosition = renderer_->getDualPosition(IntIsoPoint(currentTile.coords.toIsometric()));

        pathLayer_.add(currentTile.getDirection(nextTile), tilePosition);
        pathLayer_.add(currentTile.getDirection(nextTile), tileDualPosition);
    }
}

void PlayersDrawer::updateFogLayer(const Fog& fog) {
    fogLayer_.clear();

    for (size_t r = 0; r < fog.getRowsNo(); ++r) {
        for (size_t c = 0; c < fog.getColumnsNo(); ++c) {
            auto position = renderer_->getPosition(IntIsoPoint(c, r));
            auto dualPosition = renderer_->getDualPosition(IntIsoPoint(c, r));

            fogLayer_.add(fog(r, c), position);
            fogLayer_.add(fog(r, c), dualPosition);
        }
    }
}

}  // namespace players
