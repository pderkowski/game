/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYERSDRAWER_HPP_
#define PLAYERS_PLAYERSDRAWER_HPP_

#include <memory>
#include "SFML/Graphics.hpp"
#include "Layer.hpp"
#include "units/Unit.hpp"
#include "TileEnums.hpp"
#include "MiscellaneousEnums.hpp"
#include "MapRenderer.hpp"
#include "Selection.hpp"
#include "Tile.hpp"
#include "Fog.hpp"


namespace players {


class Players;

class PlayersDrawer {
public:
    PlayersDrawer(const Players* players, const MapRenderer* renderer);

    void draw() const;

    void toggleFog();

    void updateUnitLayer();
    void updateSelectionLayer(const Selection& selection);
    void updatePathLayer(const std::vector<Tile>& path);
    void updateFogLayer(const Fog& fog);

    void clearPathLayer();

private:
    const Players* players_;

    Layer<tileenums::Direction> pathLayer_;
    Layer<miscellaneous::Type> selectionLayer_;
    Layer<units::Unit> unitLayer_;
    Layer<TileVisibility> fogLayer_;

    const MapRenderer* renderer_;

    bool isFogToggledOn_;
};


}  // namespace players

#endif  // PLAYERS_PLAYERSDRAWER_HPP_
