/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_SELECTION_HPP_
#define PLAYERS_SELECTION_HPP_

#include "Tile.hpp"
class MapModel;


namespace players {


class Selection {
public:
    explicit Selection(const Tile& source = Tile(), const Tile& destination = Tile());

    void setSource(const Tile& source);
    void setDestination(const Tile& destination);
    void clear();

    bool isSourceSelected() const;
    bool isDestinationSelected() const;
    bool isDestinationConfirmed(const Tile& destination) const;

    Tile getSource() const;
    Tile getDestination() const;

private:
    Tile source_;
    Tile destination_;
};


}  // namespace players


#endif  // PLAYERS_SELECTION_HPP_
