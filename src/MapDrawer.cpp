/* Copyright 2014 <Piotr Derkowski> */

#include <cmath>
#include <algorithm>
#include <map>
#include <memory>
#include <iterator>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "Utils.hpp"
#include "TextureSetFactory.hpp"
#include "Resources.hpp"
#include "Layer.hpp"
#include "units/Unit.hpp"
#include "MiscellaneousEnums.hpp"

MapDrawer::MapDrawer(std::shared_ptr<MapModel> model, std::shared_ptr<sf::RenderTarget> target)
        : model_(model),
        target_(target),
        tileWidth_(96),
        tileHeight_(48),
        mapView_(sf::FloatRect(0, 0, target->getSize().x, target->getSize().y)),
        pathLayer_(TextureSetFactory::getPathTextureSet()),
        selectionLayer_(TextureSetFactory::getSelectionTextureSet()),
        unitLayer_(TextureSetFactory::getUnitTextureSet())
{
    makeLayers();
}

void MapDrawer::setModel(std::shared_ptr<MapModel> model) {
    model_ = model;
    mapView_.reset(sf::FloatRect(0, 0, target_->getSize().x, target_->getSize().y));
    makeLayers();
}

void MapDrawer::makeLayers() {
    layers_.clear();
    layers_.push_back(Layer<Tile>(TextureSetFactory::getBaseTextureSet()));
    layers_.push_back(Layer<Tile>(TextureSetFactory::getBlendTextureSet()));
    layers_.push_back(Layer<Tile>(TextureSetFactory::getGridTextureSet()));
    layers_.push_back(Layer<Tile>(TextureSetFactory::getOverlayTextureSet()));
    layers_.push_back(Layer<Tile>(TextureSetFactory::getAttributeTextureSet()));
    unitLayer_ = Layer<units::Unit>(TextureSetFactory::getUnitTextureSet());

    for (int r = 0; r < model_->getRowsNo(); ++r) {
        for (int c = 0; c < model_->getColumnsNo(); ++c) {
            auto tile = model_->getTile(IntIsoPoint(c, r));
            addTileToLayers(tile);
        }
    }

    for (auto& unit : model_->getUnits()) {
        auto tile = unit->getPosition();
        auto tilePosition = calculateTilePosition(*tile);
        auto dualTilePosition = calculateDualTilePosition(*tile);

        unitLayer_.add(*unit, tilePosition);
        unitLayer_.add(*unit, dualTilePosition);
    }
}

void MapDrawer::addTileToLayers(std::shared_ptr<const Tile> tile) {
    for (auto& layer : layers_) {
        auto tilePosition = calculateTilePosition(*tile);
        auto dualTilePosition = calculateDualTilePosition(*tile);

        layer.add(*tile, tilePosition);
        layer.add(*tile, dualTilePosition);
    }
}

void MapDrawer::draw() const {
    target_->setView(mapView_);

    for (const auto& layer : layers_) {
        target_->draw(layer);
    }

    target_->draw(pathLayer_);
    target_->draw(selectionLayer_);
    target_->draw(unitLayer_);
}

std::shared_ptr<const sf::RenderTarget> MapDrawer::getTarget() const {
    return target_;
}

std::shared_ptr<Tile> MapDrawer::getObjectByPosition(const sf::Vector2i& position) {
    target_->setView(mapView_);

    auto mapCoords = mapPixelToMapCoords(position);

    if (model_->isInBounds(mapCoords))
        return model_->getTile(mapCoords);
    else
        throw std::runtime_error("Clicked area does not point to any object.");
}

IntIsoPoint MapDrawer::mapPixelToMapCoords(const sf::Vector2i& position) {
    const int halfWidth = tileWidth_ / 2;
    const int halfHeight = tileHeight_ / 2;

    const sf::Vector2f coords = target_->mapPixelToCoords(position);
    const sf::Vector2i intCoords(lround(coords.x), lround(coords.y));
    const sf::Vector2i corner(intCoords.x - intCoords.x % halfWidth,
        intCoords.y - intCoords.y % halfHeight);
    const sf::Vector2i scaledCorner(corner.x / halfWidth, corner.y / halfHeight);

    sf::Vector2i firstCenter, otherCenter;
    if ((scaledCorner.x + scaledCorner.y) % 2 == 0) {
        firstCenter = corner;
        otherCenter = sf::Vector2i(corner.x + halfWidth, corner.y + halfHeight);
    } else {
        firstCenter = sf::Vector2i(corner.x + halfWidth, corner.y);
        otherCenter = sf::Vector2i(corner.x, corner.y + halfHeight);
    }

    const double distanceToFirst = sqrt(pow(coords.x - firstCenter.x, 2) + pow(coords.y - firstCenter.y, 2));
    const double distanceToOther = sqrt(pow(otherCenter.x - coords.x, 2) + pow(otherCenter.y - coords.y, 2));

    const sf::Vector2i closest = (distanceToFirst < distanceToOther)? firstCenter : otherCenter;
    const IntCartPoint scaledClosest = IntCartPoint(closest.x / halfWidth, closest.y / halfHeight);
    const IntIsoPoint isometric(scaledClosest.toIsometric());

    return isometric;
}

void MapDrawer::scrollView(int x, int y) {
    mapView_.move(boundShift(x, y));
    target_->setView(mapView_);
}

sf::Vector2f MapDrawer::boundShift(int x, int y) const {
    sf::Vector2f safeShift;

    sf::IntRect bounds(0, 0, getMapWidth(), getMapHeight());
    sf::IntRect displayed(mapView_.getCenter().x - mapView_.getSize().x / 2,
        mapView_.getCenter().y - mapView_.getSize().y / 2,
        mapView_.getSize().x, mapView_.getSize().y);

    int maxTopShiftPossible = bounds.top - displayed.top;
    int maxBottomShiftPossible = bounds.top + bounds.height - displayed.top - displayed.height;

    safeShift.x
        = static_cast<int>((displayed.left + x + getMapWidth()) % getMapWidth())
            - displayed.left;
    safeShift.y = (y < 0)? std::min(std::max(y, maxTopShiftPossible), maxBottomShiftPossible)
        : std::max(std::min(y, maxBottomShiftPossible), maxTopShiftPossible);

    return safeShift;
}

void MapDrawer::zoomViem(int delta, const sf::Vector2i& mousePosition) {
    target_->setView(mapView_);
    const float zoomFactor = (delta > 0)? 4.0 / 5 : 5.0 / 4;

    if (canZoom(zoomFactor)) {
        target_->setView(mapView_);
        sf::Vector2f oldCoords = target_->mapPixelToCoords(mousePosition);
        mapView_.zoom(zoomFactor);
        target_->setView(mapView_);

        sf::Vector2f newCoords = target_->mapPixelToCoords(mousePosition);
        scrollView(oldCoords.x - newCoords.x, oldCoords.y - newCoords.y);
    }
}

bool MapDrawer::canZoom(float zoomFactor) const {
    return mapView_.getSize().x * zoomFactor < getMapWidth()
        && mapView_.getSize().y * zoomFactor < getMapHeight();
}

unsigned MapDrawer::getMapWidth() const {
    return model_->getColumnsNo() * tileWidth_;
}

unsigned MapDrawer::getMapHeight() const {
    return (model_->getRowsNo() - 1) * tileHeight_ / 2;
}

sf::FloatRect MapDrawer::getDisplayedRectangle() const {
    target_->setView(mapView_);
    sf::Vector2i leftTop(0, 0);
    sf::Vector2i rightBottom(target_->getSize().x - 1, target_->getSize().y - 1);

    sf::Vector2f leftTopCoords = target_->mapPixelToCoords(leftTop);
    sf::Vector2f rightBottomCoords = target_->mapPixelToCoords(rightBottom);

    return sf::FloatRect(
        leftTopCoords.x / getMapWidth(),
        leftTopCoords.y / getMapHeight(),
        (rightBottomCoords.x - leftTopCoords.x) / getMapWidth(),
        (rightBottomCoords.y - leftTopCoords.y) / getMapHeight());
}

sf::Vector2f MapDrawer::calculateTilePosition(const Tile& tile) const {
    auto tileCartCoords = tile.coords.toCartesian();
    return sf::Vector2f(utils::positiveModulo(tileCartCoords.x * tileWidth_ / 2, 2 * getMapWidth()),
        tileCartCoords.y * tileHeight_ / 2);
}

sf::Vector2f MapDrawer::calculateDualTilePosition(const Tile& tile) const {
    auto primaryTilePosition = calculateTilePosition(tile);
    return sf::Vector2f(utils::positiveModulo(primaryTilePosition.x + getMapWidth(), 2 * getMapWidth()),
        primaryTilePosition.y);
}

void MapDrawer::updateUnitLayer(const units::Unit& unit, std::shared_ptr<const Tile> oldTile,
    std::shared_ptr<const Tile> newTile)
{
    if (oldTile) {
        auto oldPosition = calculateTilePosition(*oldTile);
        auto oldDualPosition = calculateDualTilePosition(*oldTile);
        unitLayer_.remove(unit, oldPosition);
        unitLayer_.remove(unit, oldDualPosition);
    }

    if (newTile) {
        auto newPosition = calculateTilePosition(*newTile);
        auto newDualPosition = calculateDualTilePosition(*newTile);
        unitLayer_.add(unit, newPosition);
        unitLayer_.add(unit, newDualPosition);
    }
}

void MapDrawer::updateSelectionLayer(const Selection& selection) {
    selectionLayer_.clear();

    if (selection.isSourceSelected()) {
        auto sourcePosition = calculateTilePosition(*selection.getSource());
        auto sourceDualPosition = calculateDualTilePosition(*selection.getSource());
        selectionLayer_.add(miscellaneous::Type::Source, sourcePosition);
        selectionLayer_.add(miscellaneous::Type::Source, sourceDualPosition);
    }

    if (selection.isDestinationSelected()) {
        auto destinationPosition = calculateTilePosition(*selection.getDestination());
        auto destinationDualPosition = calculateDualTilePosition(*selection.getDestination());
        selectionLayer_.add(miscellaneous::Type::Destination, destinationPosition);
        selectionLayer_.add(miscellaneous::Type::Destination, destinationDualPosition);
    }
}

void MapDrawer::updatePathLayer(const std::vector<Tile>& path) {
    pathLayer_.clear();

    for (size_t i = 0; i + 1 < path.size(); ++i) {
        const Tile& currentTile = path[i];
        const Tile& nextTile = path[i + 1];
        auto tilePosition = calculateTilePosition(currentTile);
        auto tileDualPosition = calculateDualTilePosition(currentTile);
        pathLayer_.add(currentTile.getDirection(nextTile), tilePosition);
        pathLayer_.add(currentTile.getDirection(nextTile), tileDualPosition);
    }
}
