/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "Resources.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "Utils.hpp"

MapDrawer::MapDrawer(std::shared_ptr<MapModel> model, std::shared_ptr<sf::RenderTarget> target,
    Resources& resources)
        : model_(model),
        target_(target),
        mapView_(sf::FloatRect(0, 0, target->getSize().x, target->getSize().y)),
        tileTextures_{
            { Tile::Type::Empty, resources.loadTexture("tiles/empty.png") },
            { Tile::Type::Water, resources.loadTexture("tiles/water.png") },
            { Tile::Type::Hills, resources.loadTexture("tiles/hills.png") },
            { Tile::Type::Plains, resources.loadTexture("tiles/plains.png") },
            { Tile::Type::Mountains, resources.loadTexture("tiles/mountains.png") }
        },
        tileWidth_(32),
        tileHeight_(tileWidth_ / 2)
{
    target_->setView(mapView_);
}

void MapDrawer::draw() const {
    sf::ConvexShape sprite;
    sprite.setPointCount(4);
    sprite.setPoint(0, sf::Vector2f(tileWidth_ / 2, 0));
    sprite.setPoint(1, sf::Vector2f(tileWidth_, tileHeight_ / 2));
    sprite.setPoint(2, sf::Vector2f(tileWidth_ / 2, tileHeight_));
    sprite.setPoint(3, sf::Vector2f(0, tileHeight_ / 2));
    sprite.setOrigin(tileWidth_ / 2, tileHeight_ / 2);

    const sf::Vector2f shift(tileWidth_ / 2, tileHeight_ / 2);

    for (int r = 0; r < model_->getRowsNo(); ++r) {
        for (int c = 0; c < 2 * model_->getColumnsNo(); ++c) {
            IntIsoPoint tileIsoCoords(c, r);
            auto tile = model_->getTile(tileIsoCoords);
            if (tile->isVisible) {
                auto spriteCoords = tileIsoCoords.toCartesian();
                sprite.setTexture(&tileTextures_.at(tile->type));
                sprite.setPosition(utils::positiveModulo(spriteCoords.x * shift.x, 2 * getMapWidth()),
                    spriteCoords.y * shift.y);
                target_->draw(sprite);
            }
        }
    }
}

std::shared_ptr<const sf::RenderTarget> MapDrawer::getTarget() const {
    return target_;
}

std::shared_ptr<Tile> MapDrawer::getObjectByPosition(const sf::Vector2i& position) {
    auto mapCoords = mapPixelToMapCoords(position);

    if (model_->isInBounds(mapCoords))
        return model_->getTile(mapCoords);
    else
        return std::shared_ptr<Tile>();
}

IntIsoPoint MapDrawer::mapPixelToMapCoords(const sf::Vector2i& position) {
    return IntIsoPoint(CartPoint(
        target_->mapPixelToCoords(position).x * 2 / tileWidth_,
        target_->mapPixelToCoords(position).y * 2 / tileHeight_
    ).toIsometric());
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
    delta = delta / abs(delta);

    if (canZoom(delta)) {
        sf::Vector2f currentCoords = target_->mapPixelToCoords(mousePosition);
        sf::Vector2f newCoords = getCoordsAfterZoom(delta, mousePosition);

        tileWidth_ += (2 * delta);
        tileHeight_ += delta;

        scrollView(newCoords.x - currentCoords.x, newCoords.y - currentCoords.y);
    }
}

bool MapDrawer::canZoom(int delta) const {
    const unsigned minTileSize = 8;
    const unsigned maxTileSize = 64;

    unsigned newTileWidth = tileWidth_ + 2 * delta;
    unsigned newTileHeight = tileHeight_ + delta;

    return minTileSize <= newTileWidth && newTileWidth <= maxTileSize
        && minTileSize <= newTileHeight && newTileHeight <= maxTileSize
        && (model_->getColumnsNo() * newTileWidth) >= target_->getSize().x
        && ((model_->getRowsNo() - 1) * newTileHeight / 2) >= target_->getSize().y;
}

sf::Vector2f MapDrawer::getCoordsAfterZoom(int delta, const sf::Vector2i& mousePosition) const {
    sf::Vector2f currentCoords = target_->mapPixelToCoords(mousePosition);
    double xPositionFraction = currentCoords.x / getMapWidth();
    double yPositionFraction = currentCoords.y / getMapHeight();
    return sf::Vector2f(xPositionFraction * model_->getColumnsNo() * (tileWidth_ + 2 * delta),
        yPositionFraction * (model_->getRowsNo() - 1) * (tileHeight_ + delta) / 2);
}

unsigned MapDrawer::getMapWidth() const {
    return model_->getColumnsNo() * tileWidth_;
}

unsigned MapDrawer::getMapHeight() const {
    return (model_->getRowsNo() - 1) * tileHeight_ / 2;
}

sf::FloatRect MapDrawer::getDisplayedRect() const {
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
