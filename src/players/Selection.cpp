/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "map/Tile.hpp"
#include "Selection.hpp"


namespace players {



Selection::Selection(const map::Tile& source, const map::Tile& destination)
    : source_(source), destination_(destination)
{ }

void Selection::setSource(const map::Tile& source) {
    source_ = source;
}

void Selection::setDestination(const map::Tile& destination) {
    destination_ = destination;
}

void Selection::setPath(const std::vector<map::Tile>& path) {
    path_ = path;
}

void Selection::clear() {
    source_ = map::Tile();
    destination_ = map::Tile();
    path_.clear();
}

bool Selection::isSourceSelected() const {
    return source_.isValid();
}

bool Selection::isDestinationSelected() const {
    return destination_.isValid();
}

bool Selection::isDestinationConfirmed(const map::Tile& destination) const {
    return isDestinationSelected() && getDestination() == destination;
}

bool Selection::isPathSelected() const {
    return !path_.empty();
}

map::Tile Selection::getSource() const {
    return source_;
}

map::Tile Selection::getDestination() const {
    return destination_;
}

std::vector<map::Tile> Selection::getPath() const {
    return path_;
}


}  // namespace players
