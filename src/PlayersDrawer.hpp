/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERSDRAWER_HPP_
#define PLAYERSDRAWER_HPP_

#include <memory>
#include "SFML/Graphics.hpp"
#include "Layer.hpp"
#include "units/Unit.hpp"
#include "TileEnums.hpp"
#include "MiscellaneousEnums.hpp"
#include "MapRenderer.hpp"
#include "Selection.hpp"
#include "Tile.hpp"
class Players;

class PlayersDrawer {
public:
    PlayersDrawer(const Players* players, const MapRenderer* renderer);

    void draw() const;

    void updateUnitLayer();
    void updateSelectionLayer(const Selection& selection);
    void updatePathLayer(const std::vector<Tile>& path);

private:
    const Players* players_;

    Layer<tileenums::Direction> pathLayer_;
    Layer<miscellaneous::Type> selectionLayer_;
    Layer<units::Unit> unitLayer_;

    const MapRenderer* renderer_;
};

#endif  // PLAYERSDRAWER_HPP_
