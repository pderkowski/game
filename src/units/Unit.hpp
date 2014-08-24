/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_UNIT_HPP_
#define UNITS_UNIT_HPP_

#include <functional>
#include "TileEnums.hpp"
#include "Coordinates.hpp"
#include "boost/functional/hash.hpp"
class MapModel;
class Tile;

namespace players {
    class Player;
}


namespace units {

enum class Type {
    Phalanx,
    Trireme
};

class Unit {
public:
    Unit(const IntRotPoint& coords, Type type, const MapModel* model, const players::Player* owner);

    // void setModel(const MapModel* model);
    void setMovesLeft(int movesLeft);

    Type getType() const;
    Tile getPosition() const;
    IntRotPoint getCoords() const;
    const players::Player* getOwner() const;
    int getMovesLeft() const;

    bool canMoveTo(tileenums::Direction direction) const;
    void moveTo(tileenums::Direction direction);

private:
    friend bool operator == (const Unit& lhs, const Unit& rhs);
    friend class std::hash<units::Unit>;

private:
    IntRotPoint coords_;
    Type type_;

    int movesLeft_;

    const MapModel* model_;

    const players::Player* owner_;
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
        static std::hash<const players::Player*> playerHasher;

        boost::hash_combine(seed, coordsHasher(unit.coords_));
        boost::hash_combine(seed, typeHasher(static_cast<int>(unit.type_)));
        boost::hash_combine(seed, modelHasher(unit.model_));
        boost::hash_combine(seed, playerHasher(unit.owner_));

        return seed;
    }
};


}  // namespace std

#endif  // UNITS_UNIT_HPP_
