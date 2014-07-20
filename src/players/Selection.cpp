#include <memory>
#include "Tile.hpp"
#include "units/Unit.hpp"
#include "Selection.hpp"
#include "Player.hpp"


namespace players {


Selection::Selection()
    : source_(nullptr), destination_(nullptr)
{ }

Selection::Selection(std::shared_ptr<const Tile> source)
    : source_(source), destination_(nullptr)
{ }

void Selection::setSource(std::shared_ptr<const Tile> source) {
    source_ = source;
}

void Selection::setDestination(std::shared_ptr<const Tile> destination) {
    destination_ = destination;
}

void Selection::clear() {
    source_ = nullptr;
    destination_ = nullptr;
}

bool Selection::isUnitSelected(const Player* player) const {
    return isSourceSelected() && player->hasUnitAtCoords(source_->coords);
}

bool Selection::isSourceSelected() const {
    return static_cast<bool>(source_);
}

bool Selection::isDestinationSelected() const {
    return static_cast<bool>(destination_);
}

std::shared_ptr<const Tile> Selection::getSource() const {
    return source_;
}

std::shared_ptr<const Tile> Selection::getDestination() const {
    return destination_;
}


}  // namespace players
