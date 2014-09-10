/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_MAPMODEL_HPP_
#define MAP_MAPMODEL_HPP_

#include <vector>
#include <functional>
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"


namespace map {


class MapModel {
public:
    MapModel(int rowsNo, int columnsNo);
    ~MapModel();
    MapModel(const MapModel&);
    MapModel& operator = (MapModel);

    int getRowsNo() const;
    int getColumnsNo() const;

    bool isInBounds(const IntIsoPoint& p) const;

    const Tile& getTile(const IntIsoPoint& p) const;
    Tile& getTile(const IntIsoPoint& p);

    std::vector<Tile*> getTiles(std::function<bool(Tile&)> selector);

    void changeTiles(std::function<void(Tile&)> transformation);

private:
    friend void swap(MapModel& first, MapModel& other);

    void setModelInTiles(MapModel* model);

    int rowsNo_;
    int columnsNo_;
    std::vector<std::vector<Tile>> tiles_;

};


}  // namespace map

#endif  // MAP_MAPMODEL_HPP_
