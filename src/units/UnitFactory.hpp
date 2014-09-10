/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_UNITFACTORY_HPP_
#define UNITS_UNITFACTORY_HPP_

class IntRotPoint;
namespace map { class MapModel; }
namespace units { class Unit; }
namespace players { class Player; }


namespace units {


class UnitFactory {
public:
    static Unit createPhalanx(const IntRotPoint& coords, const map::MapModel* model,
        const players::Player* owner);
    static Unit createTrireme(const IntRotPoint& coords, const map::MapModel* model,
        const players::Player* owner);
};


}


#endif  // UNITS_UNITFACTORY_HPP_
