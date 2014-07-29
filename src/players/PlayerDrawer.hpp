/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYERDRAWER_HPP_
#define PLAYERS_PLAYERDRAWER_HPP_

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


class Player;

class PlayerDrawer {
public:
    PlayerDrawer(const Player* player, const MapRenderer* renderer);

    void draw() const;

    void updateUnitLayer(const std::vector<units::Unit>& visibleUnits);
    void updateSelectionLayer();
    void updatePathLayer(const std::vector<Tile>& path);
    void updateFogLayer();

    void clearPathLayer();

    void setPointer(const Player* player);

private:
    const Player* player_;

    Layer<tileenums::Direction> pathLayer_;
    Layer<miscellaneous::Type> selectionLayer_;
    Layer<units::Unit> unitLayer_;
    Layer<TileVisibility> fogLayer_;

    const MapRenderer* renderer_;

};


}  // namespace players

#endif  // PLAYERS_PLAYERDRAWER_HPP_
