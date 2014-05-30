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
        tileWidth_(96),
        tileHeight_(48),
        mapView_(sf::FloatRect(0, 0, target->getSize().x, target->getSize().y)),
        texture_(resources.loadTexture("tiles/terrain1.png")),
        textureCoords_{
            { Tile::Type::Hills, sf::Vector2f(1, 197) },
            { Tile::Type::Mountains, sf::Vector2f(1, 246) },
            { Tile::Type::Plains, sf::Vector2f(1, 99) },
            { Tile::Type::Water, sf::Vector2f(98, 1) }
        },
        mapVertices_(sf::Quads, 4 * model->getRowsNo() * 2 * model->getColumnsNo())
{
    texture_.setSmooth(true);
    setMapVertices();
}

void MapDrawer::setModel(std::shared_ptr<MapModel> model) {
    model_ = model;
    mapView_.reset(sf::FloatRect(0, 0, target_->getSize().x, target_->getSize().y));
    mapVertices_.resize(4 * model->getRowsNo() * 2 * model->getColumnsNo());
    setMapVertices();
}

void MapDrawer::setMapVertices() {
    for (int r = 0; r < model_->getRowsNo(); ++r) {
        for (int c = 0; c < 2 * model_->getColumnsNo(); ++c) {
            IntIsoPoint tileIsoCoords(c, r);
            auto tile = model_->getTile(tileIsoCoords);
            auto spriteCoords = tileIsoCoords.toCartesian();

            sf::Vertex* quad = &mapVertices_[(c + r * 2 * model_->getColumnsNo()) * 4];

            sf::Vector2f quadCenter(
                utils::positiveModulo(spriteCoords.x * tileWidth_ / 2, 2 * getMapWidth()),
                spriteCoords.y * tileHeight_ / 2);

            quad[0].position = sf::Vector2f(quadCenter.x - tileWidth_ / 2,
                quadCenter.y - tileHeight_ / 2);
            quad[1].position = sf::Vector2f(quadCenter.x + tileWidth_ / 2,
                quadCenter.y - tileHeight_ / 2);
            quad[2].position = sf::Vector2f(quadCenter.x + tileWidth_ / 2,
                quadCenter.y + tileHeight_ / 2);
            quad[3].position = sf::Vector2f(quadCenter.x - tileWidth_ / 2,
                quadCenter.y + tileHeight_ / 2);

            sf::Vector2f texTopLeft = textureCoords_.at(tile->type);

            quad[0].texCoords = sf::Vector2f(texTopLeft.x, texTopLeft.y);
            quad[1].texCoords = sf::Vector2f(texTopLeft.x + tileWidth_, texTopLeft.y);
            quad[2].texCoords = sf::Vector2f(texTopLeft.x + tileWidth_, texTopLeft.y + tileHeight_);
            quad[3].texCoords = sf::Vector2f(texTopLeft.x, texTopLeft.y + tileHeight_);
        }
    }
}

void MapDrawer::draw() const {
    auto states = sf::RenderStates::Default;
    states.texture = &texture_;
    target_->setView(mapView_);
    target_->draw(mapVertices_, states);
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
