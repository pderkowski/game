/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYERS_HPP_
#define PLAYERS_PLAYERS_HPP_

#include <vector>
#include "units/Unit.hpp"
#include "units/Units.hpp"
#include "Player.hpp"
#include "PlayersDrawer.hpp"
#include "UnitController.hpp"
#include "Subject.hpp"
#include "Action.hpp"
namespace map { class MapModel; }
namespace map { class Tile; }
class Renderer;


namespace players {


class Players : public Subject<ActionNotification>, public Observer<ActionType> {
public:
    Players(int numberOfPlayers, const map::MapModel* model, const Renderer* renderer);
    virtual ~Players() { }

    void switchToNextPlayer();

    Player* getCurrentPlayer();
    const Player* getCurrentPlayer() const;

    bool isUnitSelected() const;
    units::Unit getSelectedUnit() const;

    void setModel(const map::MapModel* model);

    void draw() const;

    void handleLeftClick(const map::Tile& clickedTile);
    void handleRightClick(const map::Tile& clickedTile);
    void handleAPressed();
    void handleFPressed();
    void handleDPressed();

private:
    std::vector<units::Unit> getVisibleUnits() const;

    virtual void notify(ActionType action) const;
    virtual void onNotify(const ActionType& ntion);

private:
    unsigned currentPlayer_;
    std::vector<Player> players_;

    units::Units units_;

    PlayersDrawer drawer_;
};


}  // namespace players

#endif  // PLAYERS_PLAYERS_HPP_
