/* Copyright 2014 <Piotr Derkowski> */

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

void Selection::clear() {
    source_ = Tile();
    destination_ = Tile();
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

Tile Selection::getSource() const {
    return source_;
}

Tile Selection::getDestination() const {
    return destination_;
}


}  // namespace players
