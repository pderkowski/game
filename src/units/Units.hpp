/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_UNITS_HPP_
#define UNITS_UNITS_HPP_

#include <vector>
#include "Unit.hpp"
#include "UnitSelection.hpp"

namespace units {


class Units {
public:
    UnitSelection select();
    ConstUnitSelection select() const;

    void add(const Unit& unit);
    void remove(const Unit& unit);

    void clear();

private:
    std::vector<Unit*> getPointersToUnits();
    std::vector<const Unit*> getPointersToConstUnits() const;

private:
    std::vector<Unit> units_;
};


}  // namespace units

#endif  // UNITS_UNITS_HPP_
