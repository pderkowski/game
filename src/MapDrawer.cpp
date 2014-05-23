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
        tileSize_(32)
{
    target_->setView(mapView_);
}

void MapDrawer::draw() const {
    sf::CircleShape sprite(tileSize_ / 2, 4);
    sprite.setOrigin(tileSize_ / 2, tileSize_ / 2);

    const sf::Vector2f shift(tileSize_ / 2, tileSize_ / 2);

    for (int r = 0; r < model_->getRowsNo(); ++r) {
        for (int c = 0; c < 2 * model_->getColumnsNo(); ++c) {
            IntIsoPoint tileIsoCoords(c, r);
            auto tile = model_->getTile(tileIsoCoords);
            if (tile->isVisible) {
                auto spriteCoords = tileIsoCoords.toCartesian();
                sprite.setTexture(&tileTextures_.at(tile->type));
                sprite.setPosition(utils::positiveModulo(spriteCoords.x * shift.x, 2 * getMapWidth(tileSize_)),
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
        target_->mapPixelToCoords(position).x * 2 / tileSize_,
        target_->mapPixelToCoords(position).y * 2 / tileSize_
    ).toIsometric());
}

void MapDrawer::scrollView(int x, int y) {
    mapView_.move(boundShift(x, y));
    target_->setView(mapView_);
}

sf::Vector2f MapDrawer::boundShift(int x, int y) const {
    sf::Vector2f safeShift;

    sf::IntRect bounds(0, 0, getMapWidth(tileSize_), getMapHeight(tileSize_));
    sf::IntRect displayed(mapView_.getCenter().x - mapView_.getSize().x / 2,
        mapView_.getCenter().y - mapView_.getSize().y / 2,
        mapView_.getSize().x, mapView_.getSize().y);

    int maxTopShiftPossible = bounds.top - displayed.top;
    int maxBottomShiftPossible = bounds.top + bounds.height - displayed.top - displayed.height;

    safeShift.x
        = static_cast<int>((displayed.left + x + getMapWidth(tileSize_)) % getMapWidth(tileSize_))
            - displayed.left;
    safeShift.y = (y < 0)? std::min(std::max(y, maxTopShiftPossible), maxBottomShiftPossible)
        : std::max(std::min(y, maxBottomShiftPossible), maxTopShiftPossible);

    return safeShift;
}

void MapDrawer::zoomViem(int delta, const sf::Vector2i& mousePosition) {
    delta = 2 * delta / abs(delta);

    if (canZoom(delta)) {
        sf::Vector2f currentCoords = target_->mapPixelToCoords(mousePosition);
        sf::Vector2f newCoords = getCoordsAfterZoom(delta, mousePosition);

        tileSize_ += (delta);

        scrollView(newCoords.x - currentCoords.x, newCoords.y - currentCoords.y);
    }
}

bool MapDrawer::canZoom(int delta) const {
    const int minTileSize = 8;
    const int maxTileSize = 64;

    int newTileSize = tileSize_ + delta;
    return newTileSize >= minTileSize
        && newTileSize <= maxTileSize
        && getMapWidth(newTileSize) >= target_->getSize().x
        && getMapHeight(newTileSize) >= target_->getSize().y;
}

sf::Vector2f MapDrawer::getCoordsAfterZoom(int delta, const sf::Vector2i& mousePosition) const {
    sf::Vector2f currentCoords = target_->mapPixelToCoords(mousePosition);
    double xPositionFraction = currentCoords.x / getMapWidth(tileSize_);
    double yPositionFraction = currentCoords.y / getMapHeight(tileSize_);
    return sf::Vector2f(xPositionFraction * getMapWidth(tileSize_ + delta),
        yPositionFraction * getMapHeight(tileSize_ + delta));
}

unsigned MapDrawer::getMapWidth(int tileSize) const {
    return model_->getColumnsNo() * tileSize;
}

unsigned MapDrawer::getMapHeight(int tileSize) const {
    return (model_->getRowsNo() - 1) * tileSize / 2;
}

sf::FloatRect MapDrawer::getDisplayedRect() const {
    sf::Vector2i leftTop(0, 0);
    sf::Vector2i rightBottom(target_->getSize().x - 1, target_->getSize().y - 1);

    sf::Vector2f leftTopCoords = target_->mapPixelToCoords(leftTop);
    sf::Vector2f rightBottomCoords = target_->mapPixelToCoords(rightBottom);

    return sf::FloatRect(
        leftTopCoords.x / getMapWidth(tileSize_),
        leftTopCoords.y / getMapHeight(tileSize_),
        (rightBottomCoords.x - leftTopCoords.x) / getMapWidth(tileSize_),
        (rightBottomCoords.y - leftTopCoords.y) / getMapHeight(tileSize_));
}
