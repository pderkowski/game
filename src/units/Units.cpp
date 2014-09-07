/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <algorithm>
#include "Unit.hpp"
#include "UnitSelection.hpp"
#include "Units.hpp"


namespace units {


UnitSelection Units::select() {
    return UnitSelection(getPointersToUnits());
}

ConstUnitSelection Units::select() const {
    return ConstUnitSelection(getPointersToConstUnits());
}

void Units::add(const Unit& unit) {
    units_.push_back(unit);
}

void Units::remove(const Unit& unit) {
    auto newRangeEnd = std::remove(units_.begin(), units_.end(), unit);
    units_.erase(newRangeEnd, units_.end());
}

void Units::clear() {
    units_.clear();
}

std::vector<Unit*> Units::getPointersToUnits() {
    std::vector<Unit*> pointers;

    for (Unit& unit : units_) {
        pointers.push_back(&unit);
    }

    return pointers;
}

std::vector<const Unit*> Units::getPointersToConstUnits() const {
    std::vector<const Unit*> pointers;

    for (const Unit& unit : units_) {
        pointers.push_back(&unit);
    }

    return pointers;
}


}  // namespace units
