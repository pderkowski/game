/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_UNIT_HPP_
#define UNITS_UNIT_HPP_

#include <string>
#include <functional>
#include "TileEnums.hpp"
#include "Coordinates.hpp"
#include "UnitProperties.hpp"
#include "boost/functional/hash.hpp"
class MapModel;
class Tile;
namespace players { class Player; }


namespace units {


class Unit {
public:
    Unit(const IntRotPoint& coords,
        const UnitProperties& properties,
        const MapModel* model,
        const players::Player* owner);

    void resetMoves();
    void setMovesLeft(int movesLeft);
    void setHpLeft(int hpLeft);

    std::string getName() const;
    Type getType() const;
    Tile getPosition() const;
    IntRotPoint getCoords() const;
    const players::Player* getOwner() const;

    int getMovesLeft() const;
    int getHpLeft() const;
    int getBaseHp() const;
    int getBaseMoves() const;

    bool canMoveTo(tileenums::Direction direction) const;
    void moveTo(tileenums::Direction direction);

private:
    friend bool operator == (const Unit& lhs, const Unit& rhs);
    friend class std::hash<units::Unit>;

private:
    IntRotPoint coords_;

    UnitProperties properties_;

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
        static std::hash<IntRotPoint> coordsHasher;
        return coordsHasher(unit.coords_);
    }
};


}  // namespace std

#endif  // UNITS_UNIT_HPP_
