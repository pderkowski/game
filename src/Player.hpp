/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>
#include "units/Unit.hpp"
#include "Coordinates.hpp"

class Player {
public:
    Player();
    explicit Player(const std::string& name);

    std::string getName() const;

    bool hasUnitAtCoords(const IntRotPoint& coords) const;

    const units::Unit* getUnitAtCoords(const IntRotPoint& coords) const;
    units::Unit* getUnitAtCoords(const IntRotPoint& coords);

    std::vector<const units::Unit*> getAllUnits() const;

    void addUnit(const units::Unit& unit);

private:
    std::string name_;

    std::vector<units::Unit> units_;
};

#endif  // PLAYER_HPP_
