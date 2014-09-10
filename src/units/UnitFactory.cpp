/* Copyright 2014 <Piotr Derkowski> */

#include "Coordinates.hpp"
#include "map/MapModel.hpp"
#include "Unit.hpp"
#include "players/Player.hpp"
#include "UnitProperties.hpp"
#include "UnitFactory.hpp"


namespace units {


Unit UnitFactory::createPhalanx(const IntRotPoint& coords, const map::MapModel* model,
    const players::Player* owner)
{
    UnitProperties phalanxProperties{ "Phalanx", Type::Phalanx, 4, 4, 4, 0 };
    return Unit(coords, phalanxProperties, model, owner);
}

Unit UnitFactory::createTrireme(const IntRotPoint& coords, const map::MapModel* model,
    const players::Player* owner)
{
    UnitProperties triremeProperties{ "Trireme", Type::Trireme, 3, 3, 5, 0 };
    return Unit(coords, triremeProperties, model, owner);
}


}
