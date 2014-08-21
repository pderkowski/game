/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_SELECTION_HPP_
#define PLAYERS_SELECTION_HPP_

#include <vector>
#include "Tile.hpp"


namespace players {


class Selection {
public:
    explicit Selection(const Tile& source = Tile(), const Tile& destination = Tile());

    void setSource(const Tile& source);
    void setDestination(const Tile& destination);
    void setPath(const std::vector<Tile>& path);
    void clear();

    bool isSourceSelected() const;
    bool isDestinationSelected() const;
    bool isDestinationConfirmed(const Tile& destination) const;
    bool isPathSelected() const;

    Tile getSource() const;
    Tile getDestination() const;
    std::vector<Tile> getPath() const;

private:
    Tile source_;
    Tile destination_;

    std::vector<Tile> path_;
};


}  // namespace players


#endif  // PLAYERS_SELECTION_HPP_
