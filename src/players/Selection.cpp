/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "Tile.hpp"
#include "Selection.hpp"


namespace players {



Selection::Selection(const Tile& source, const Tile& destination)
    : source_(source), destination_(destination)
{ }

void Selection::setSource(const Tile& source) {
    source_ = source;
}

void Selection::setDestination(const Tile& destination) {
    destination_ = destination;
}

void Selection::setPath(const std::vector<Tile>& path) {
    path_ = path;
}

void Selection::clear() {
    source_ = Tile();
    destination_ = Tile();
    path_.clear();
}

bool Selection::isSourceSelected() const {
    return source_.isValid();
}

bool Selection::isDestinationSelected() const {
    return destination_.isValid();
}

bool Selection::isDestinationConfirmed(const Tile& destination) const {
    return isDestinationSelected() && getDestination() == destination;
}

bool Selection::isPathSelected() const {
    return !path_.empty();
}

Tile Selection::getSource() const {
    return source_;
}

Tile Selection::getDestination() const {
    return destination_;
}

std::vector<Tile> Selection::getPath() const {
    return path_;
}


}  // namespace players
