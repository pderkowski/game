/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include "SFML/Graphics.hpp"
#include "Layer.hpp"
#include "TextureSet.hpp"
#include "Tile.hpp"
#include "ModifiableLayer.hpp"

void ModifiableLayer::add(std::shared_ptr<const Tile> tile, const sf::Vector2f& tileCenter) {
    if (positions_.find(tile) == positions_.end()) {
        size_t sizeBefore = vertices_.getVertexCount();

        Layer::add(tile, tileCenter);

        size_t sizeAfter = vertices_.getVertexCount();

        if (sizeAfter > sizeBefore) {
            positions_.insert(std::make_pair(tile, VertexPosition{ sizeBefore, sizeAfter - sizeBefore }));
        }
    }
}

void ModifiableLayer::remove(std::shared_ptr<const Tile> tile) {
    if (positions_.find(tile) != positions_.end()) {
        auto position = positions_.at(tile);
        removeVertices(position);
        positions_.erase(tile);
        updatePositions(position);
    }
}

void ModifiableLayer::update(std::shared_ptr<const Tile> tile, const sf::Vector2f& tileCenter) {
    remove(tile);
    add(tile, tileCenter);
}

void ModifiableLayer::removeVertices(const VertexPosition& position) {
    for (size_t pos = position.start + position.size; pos != vertices_.getVertexCount(); ++pos) {
        vertices_[pos - position.size] = vertices_[pos];
        vertices_.resize(vertices_.getVertexCount() - position.size);
    }
}

void ModifiableLayer::updatePositions(const VertexPosition& position) {
    for (auto& tile_position : positions_) {
        if (tile_position.second.start > position.start)
            tile_position.second.start -= position.size;
    }
}
