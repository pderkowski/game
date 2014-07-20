/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "Tile.hpp"
#include "Fog.hpp"
#include "Coordinates.hpp"


namespace players {

Fog::Fog(size_t rows, size_t columns)
    : rows_(rows), columns_(columns),
    tiles_(rows, std::vector<TileVisibility>(columns, TileVisibility::Unknown))
{ }

const TileVisibility& Fog::operator ()(size_t row, size_t column) const {
    return tiles_[row][column];
}

TileVisibility& Fog::operator ()(size_t row, size_t column) {
    return tiles_[row][column];
}

size_t Fog::getRowsNo() const {
    return rows_;
}

size_t Fog::getColumnsNo() const {
    return columns_;
}

void Fog::addVisible(const std::vector<Tile>& tiles) {
    for (const auto& tile : tiles) {
        IntIsoPoint coords(tile.coords.toIsometric());
        tiles_[coords.y][coords.x] = TileVisibility::VisibleKnown;
    }
}
void Fog::addKnown(const std::vector<Tile>& tiles) {
    for (const auto& tile : tiles) {
        IntIsoPoint coords(tile.coords.toIsometric());

        if (tiles_[coords.y][coords.x] == TileVisibility::Unknown) {
            tiles_[coords.y][coords.x] = TileVisibility::UnvisibleKnown;
        }
    }
}

void Fog::removeVisible(const std::vector<Tile>& tiles) {
    for (const auto& tile : tiles) {
        IntIsoPoint coords(tile.coords.toIsometric());

        if (tiles_[coords.y][coords.x] == TileVisibility::VisibleKnown) {
            tiles_[coords.y][coords.x] = TileVisibility::UnvisibleKnown;
        }
    }
}

}  // namespace players
