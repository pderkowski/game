/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <iterator>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "Utils.hpp"
#include "TextureSetFactory.hpp"
#include "Resources.hpp"

MapDrawer::MapDrawer(std::shared_ptr<MapModel> model, std::shared_ptr<sf::RenderTarget> target)
        : model_(model),
        target_(target),
        tileWidth_(96),
        tileHeight_(48),
        mapView_(sf::FloatRect(0, 0, target->getSize().x, target->getSize().y))
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
    layers_.push_back(Layer(TextureSetFactory::getTerrainTextureSet()));
    layers_.push_back(Layer(TextureSetFactory::getLandmarkTextureSet()));

    for (int r = 0; r < model_->getRowsNo(); ++r) {
        for (int c = 0; c < model_->getColumnsNo(); ++c) {
            auto tile = model_->getTile(IntIsoPoint(c, r));
            addTileToLayers(tile);
        }
    }
}

void MapDrawer::addTileToLayers(std::shared_ptr<const Tile> tile) {
    for (auto& layer : layers_) {
        if (layer.contains(tile->type)) {
            auto tileCartCoords = tile->coords.toCartesian();
            sf::Vector2f tilePosition(
                utils::positiveModulo(tileCartCoords.x * tileWidth_ / 2, 2 * getMapWidth()),
                tileCartCoords.y * tileHeight_ / 2);
            sf::Vector2f dualTilePosition(
                utils::positiveModulo(tilePosition.x + getMapWidth(), 2 * getMapWidth()),
                tilePosition.y);

            layer.add(tile, model_->getNeighbors(tile), tilePosition);
            layer.add(tile, model_->getNeighbors(tile), dualTilePosition);
        }
    }
}

void MapDrawer::draw() const {
    target_->setView(mapView_);

    for (const auto& layer : layers_) {
        target_->draw(layer);
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
