/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "Tile.hpp"
#include "Fog.hpp"
#include "Coordinates.hpp"


namespace players {

Fog::Fog(size_t rows, size_t columns)
    : rows_(rows), columns_(columns),
    tiles_(rows, std::vector<int>(columns, -1)),
    isFogToggledOn_(true)
{ }

TileVisibility Fog::operator ()(size_t row, size_t column) const {
    return translate(tiles_[row][column]);
}

size_t Fog::getRowsNo() const {
    return rows_;
}

size_t Fog::getColumnsNo() const {
    return columns_;
}

void Fog::addVisible(const std::vector<const Tile*>& tiles) {
    for (const Tile* tile : tiles) {
        IntIsoPoint coords(tile->coords.toIsometric());
        if (tiles_[coords.y][coords.x] < 0) {
            tiles_[coords.y][coords.x] = 1;
        } else {
            ++tiles_[coords.y][coords.x];
        }
    }
}

void Fog::toggle() {
    isFogToggledOn_ = !isFogToggledOn_;
}

void Fog::clear() {
    for (auto& row : tiles_) {
        for (auto& tile : row) {
            tile = -1;
        }
    }
}

void Fog::removeVisible(const std::vector<const Tile*>& tiles) {
    for (const Tile* tile : tiles) {
        IntIsoPoint coords(tile->coords.toIsometric());
        --tiles_[coords.y][coords.x];
    }
}

TileVisibility Fog::translate(int code) const {
    if (isFogToggledOn_) {
        if (code < 0) {
            return TileVisibility::Unknown;
        } else if (code == 0) {
            return TileVisibility::UnvisibleKnown;
        } else {
            return TileVisibility::VisibleKnown;
        }
    } else {
        return TileVisibility::VisibleKnown;
    }
}


}  // namespace players
