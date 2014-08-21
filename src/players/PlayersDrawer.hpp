/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYERSDRAWER_HPP_
#define PLAYERS_PLAYERSDRAWER_HPP_

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


class PlayersDrawer {
public:
    PlayersDrawer(const MapRenderer* renderer);

    void draw() const;

    void updateUnitLayer(const std::vector<units::Unit>& visibleUnits);
    void updateSelectionLayer(const Selection& selection);
    void updatePathLayer(const Selection& selection);
    void updateFogLayer(const Fog& fog);

private:
    Layer<tileenums::Direction> pathLayer_;
    Layer<miscellaneous::Type> selectionLayer_;
    Layer<units::Unit> unitLayer_;
    Layer<TileVisibility> fogLayer_;

    const MapRenderer* renderer_;
};


}  // namespace players

#endif  // PLAYERS_PLAYERSDRAWER_HPP_
