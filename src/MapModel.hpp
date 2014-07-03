/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPMODEL_HPP_
#define MAPMODEL_HPP_

#include <vector>
#include <memory>
#include <functional>
#include "Tile.hpp"
#include "HeightMap.hpp"
#include "Coordinates.hpp"

class MapModel {
public:
    typedef std::function<Tile::Type(double)> HeightToTileConverter;

    MapModel(int rowsNo, int columnsNo);

    int getRowsNo() const;
    int getColumnsNo() const;

    bool isInBounds(const IntIsoPoint& p) const;
    bool isInBounds(std::shared_ptr<const Tile> tile) const;

    std::shared_ptr<const Tile> getTile(const IntIsoPoint& p) const;
    std::shared_ptr<Tile> getTile(const IntIsoPoint& p);

    std::vector<std::shared_ptr<const Tile>> getTilesByType(Tile::Type type) const;
    std::vector<std::shared_ptr<const Tile>> getTiles(std::function<bool(const Tile&)> selector) const;

    std::vector<std::shared_ptr<const Tile>> getNeighbors(std::shared_ptr<const Tile> tile) const;
    std::vector<std::shared_ptr<const Tile>> getNeighbors(const Tile& tile) const;

    std::vector<std::shared_ptr<const Tile>> getAdjacentNeighbors(std::shared_ptr<const Tile> tile) const;
    std::vector<std::shared_ptr<const Tile>> getAdjacentNeighbors(const Tile& tile) const;

    void changeTiles(std::function<void(Tile&)> transformation);

private:
    int rowsNo_;
    int columnsNo_;
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
};

#endif  // MAPMODEL_HPP_
