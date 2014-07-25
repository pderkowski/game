#include "Tile.hpp"
#include "units/Unit.hpp"
#include "Selection.hpp"
#include "Player.hpp"


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

bool Selection::isUnitSelected(const Player* player) const {
    return isSourceSelected() && player->hasUnitAtCoords(source_.coords);
}

bool Selection::isSourceSelected() const {
    return source_.isValid();
}

bool Selection::isDestinationSelected() const {
    return destination_.isValid();
}

Tile Selection::getSource() const {
    return source_;
}

Tile Selection::getDestination() const {
    return destination_;
}


}  // namespace players
