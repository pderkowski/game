/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPMODEL_HPP_
#define MAPMODEL_HPP_

#include <vector>
#include <memory>
#include <functional>
#include "Tile.hpp"
#include "Gradient.hpp"
#include "HeightMap.hpp"

class MapModel {
public:
    typedef std::function<Tile::Type(double)> HeightToTileConverter;

    MapModel(int rowsNo, int columnsNo);
    MapModel(const HeightMap& heightMap, HeightToTileConverter converter);
    MapModel(const HeightMap& heightMap, const Gradient& gradient);

    int getRowsNo() const;
    int getColumnsNo() const;

    std::shared_ptr<const Tile> getTile(int row, int column) const;
    std::shared_ptr<Tile> getTile(int row, int column);

    static const int OutOfBounds = -1;

private:
    int rowsNo_;
    int columnsNo_;
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
};

#endif  // MAPMODEL_HPP_
