/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAMENOTIFICATION_HPP_
#define GAMENOTIFICATION_HPP_

namespace map { class MapModel; }
namespace players { class Player; }


struct GameNotification {
    enum Type {
        NewMapGenerated,
        FogToggled,
        UnitAdded,
        UnitRemoved,
        PlayerSwitched,
        PrimarySelectionSet,
        SecondarySelectionSet
    };

    Type type;

    const map::MapModel* map;
    const players::Player* player;
};


#endif  // GAMENOTIFICATION_HPP_
