/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_SELECTION_HPP_
#define PLAYERS_SELECTION_HPP_

#include <vector>
#include "map/Tile.hpp"


namespace players {


class Selection {
public:
    explicit Selection(const map::Tile& source = map::Tile(), const map::Tile& destination = map::Tile());

    void setSource(const map::Tile& source);
    void setDestination(const map::Tile& destination);
    void setPath(const std::vector<map::Tile>& path);
    void clear();

    bool isSourceSelected() const;
    bool isDestinationSelected() const;
    bool isDestinationConfirmed(const map::Tile& destination) const;
    bool isPathSelected() const;

    map::Tile getSource() const;
    map::Tile getDestination() const;
    std::vector<map::Tile> getPath() const;

private:
    map::Tile source_;
    map::Tile destination_;

    std::vector<map::Tile> path_;
};


}  // namespace players


#endif  // PLAYERS_SELECTION_HPP_
