/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPMODEL_HPP_
#define MAPMODEL_HPP_

#include <vector>
#include <memory>
#include <functional>
#include "Tile.hpp"
#include "HeightMap.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
#include "units/Unit.hpp"

class MapModel {
public:
    MapModel(int rowsNo, int columnsNo);
    ~MapModel();
    MapModel(const MapModel&);
    MapModel& operator = (MapModel);

    int getRowsNo() const;
    int getColumnsNo() const;

    bool isInBounds(const IntIsoPoint& p) const;
    bool isInBounds(std::shared_ptr<const Tile> tile) const;

    std::shared_ptr<const Tile> getTile(const IntIsoPoint& p) const;
    std::shared_ptr<Tile> getTile(const IntIsoPoint& p);

    std::vector<std::shared_ptr<const Tile>> getTilesByType(tileenums::Type type) const;
    std::vector<std::shared_ptr<const Tile>> getTiles(std::function<bool(const Tile&)> selector) const;

    void changeTiles(std::function<void(Tile&)> transformation);

    void addUnit(const units::Unit& unit);
    const std::vector<units::Unit>& getUnits() const;
    std::vector<units::Unit>& getUnits();

private:
    friend void swap(MapModel& first, MapModel& other);

    void setModelInTiles(const MapModel* model);
    void setModelInUnits(const MapModel* model);

    int rowsNo_;
    int columnsNo_;
    std::vector<units::Unit> units_;
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
};

#endif  // MAPMODEL_HPP_
