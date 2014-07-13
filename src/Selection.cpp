#include <memory>
#include "Tile.hpp"
#include "units/Unit.hpp"
#include "Selection.hpp"


Selection::Selection()
{ }

Selection::Selection(std::shared_ptr<Tile> source)
    : source_(source)
{ }

void Selection::setSource(std::shared_ptr<Tile> source) {
    source_ = source;
}

void Selection::setDestination(std::shared_ptr<Tile> destination) {
    destination_ = destination;
}

void Selection::clear() {
    source_ = nullptr;
    destination_ = nullptr;
}

bool Selection::isUnitSelected() const {
    return isSourceSelected() && !source_->getUnits().empty();
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

units::Unit* Selection::getSelectedUnit() const {
    return source_->getUnits().front();
}
