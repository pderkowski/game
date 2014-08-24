/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYERSDRAWER_HPP_
#define PLAYERS_PLAYERSDRAWER_HPP_

#include "SFML/Graphics.hpp"
#include "Layer.hpp"
#include "units/Unit.hpp"
#include "TileEnums.hpp"
#include "MiscellaneousEnums.hpp"
#include "Renderer.hpp"
#include "Selection.hpp"
#include "Tile.hpp"
#include "Fog.hpp"


namespace players {


class PlayersDrawer {
public:
    PlayersDrawer(const Renderer* renderer);

    void draw() const;

    void updateUnitLayer(const std::vector<units::Unit>& visibleUnits);
    void updateFlagLayer(const std::vector<units::Unit>& visibleUnits);
    void updateSelectionLayer(const Selection& selection);
    void updatePathLayer(const Selection& selection);
    void updateFogLayer(const Fog& fog);

private:
    Layer<tileenums::Direction> pathLayer_;
    Layer<miscellaneous::Type> selectionLayer_;
    Layer<units::Unit> unitLayer_;
    Layer<miscellaneous::Flag> flagLayer_;
    Layer<TileVisibility> fogLayer_;

    const Renderer* renderer_;
};


}  // namespace players

#endif  // PLAYERS_PLAYERSDRAWER_HPP_
