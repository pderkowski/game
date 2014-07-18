/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_UNIT_HPP_
#define UNITS_UNIT_HPP_

#include <memory>
#include <map>
#include <functional>
#include "TileEnums.hpp"
#include "Coordinates.hpp"
#include "boost/functional/hash.hpp"
class MapModel;
class Tile;

namespace units {

enum class Type {
    Phalanx
};

class Unit {
public:
    Unit(const IntRotPoint& coords, Type type, const MapModel* model = nullptr);

    void setModel(const MapModel* model);

    Type getType() const;

    std::shared_ptr<const Tile> getPosition() const;
    IntRotPoint getCoords() const;

    bool canMoveTo(tileenums::Direction direction) const;
    void moveTo(tileenums::Direction direction);

    std::map<tileenums::Type, unsigned> getMovingCosts() const;

private:
    friend bool operator == (const Unit& lhs, const Unit& rhs);
    friend class std::hash<units::Unit>;

    IntRotPoint coords_;
    Type type_;
    const MapModel* model_;
};

bool operator == (const Unit& lhs, const Unit& rhs);

}  // namespace units


namespace std {


template <>
struct hash<units::Unit>
{
    std::size_t operator()(const units::Unit& unit) const
    {
        std::size_t seed = 0;

        static std::hash<IntRotPoint> coordsHasher;
        static std::hash<int> typeHasher;
        static std::hash<const MapModel*> modelHasher;

        boost::hash_combine(seed, coordsHasher(unit.coords_));
        boost::hash_combine(seed, typeHasher(static_cast<int>(unit.type_)));
        boost::hash_combine(seed, modelHasher(unit.model_));

        return seed;
    }
};


}  // namespace std

#endif  // UNITS_UNIT_HPP_
