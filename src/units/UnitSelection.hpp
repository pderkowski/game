/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_UNITSELECTION_HPP_
#define UNITS_UNITSELECTION_HPP_

#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include "Unit.hpp"
#include "Tile.hpp"
#include "players/Player.hpp"
namespace units { template <class T> class UnitSelectionIterator; }


namespace units {

// forward declarations
template <class T> class UnitSelectionImpl;

typedef UnitSelectionImpl<Unit> UnitSelection;
typedef UnitSelectionImpl<const Unit> ConstUnitSelection;

template <class T> class UnitSelectionIterator;

template <class T>
bool operator == (const UnitSelectionIterator<T>& lhs, const UnitSelectionIterator<T>& rhs);
template <class T>
bool operator != (const UnitSelectionIterator<T>& lhs, const UnitSelectionIterator<T>& rhs);



template <class T>
class UnitSelectionImpl {
public:
    friend class UnitSelectionIterator<T>;

    typedef UnitSelectionIterator<T> iterator;

public:
    explicit UnitSelectionImpl(const std::vector<T*>& selection);

    T& operator [](size_t position);

    UnitSelectionImpl nameEqual(const std::string& queriedName) const;
    UnitSelectionImpl typeEqual(Type queriedType) const;
    UnitSelectionImpl tileEqual(const Tile& queriedType) const;
    UnitSelectionImpl playerEqual(const players::Player* queriedPlayer) const;
    UnitSelectionImpl playerNotEqual(const players::Player* queriedPlayer) const;

    size_t size() const;

    bool empty() const;

    iterator begin();
    iterator end();

private:
    std::vector<T*> selection_;
};


template <class T>
class UnitSelectionIterator : public std::iterator<std::forward_iterator_tag, T> {
public:
    UnitSelectionIterator(UnitSelectionImpl<T>* selection, size_t position);
    virtual ~UnitSelectionIterator() { }

    T& operator *();
    UnitSelectionIterator<T>& operator++();
    UnitSelectionIterator<T> operator++(int);

    friend bool operator == <>(const UnitSelectionIterator<T>& lhs, const UnitSelectionIterator<T>& rhs);
    friend bool operator != <>(const UnitSelectionIterator<T>& lhs, const UnitSelectionIterator<T>& rhs);

private:
    UnitSelectionImpl<T>* selection_;
    size_t position_;
};


template <class T>
UnitSelectionImpl<T>::UnitSelectionImpl(const std::vector<T*>& selection)
    : selection_(selection)
{ }

template <class T>
T& UnitSelectionImpl<T>::operator [](size_t position) {
    return *(selection_.at(position));
}

template <class T>
size_t UnitSelectionImpl<T>::size() const {
    return selection_.size();
}

template <class T>
bool UnitSelectionImpl<T>::empty() const {
    return selection_.empty();
}

template <class T>
UnitSelectionImpl<T> UnitSelectionImpl<T>::nameEqual(const std::string& queriedName) const {
    std::vector<T*> newSelection;
    std::copy_if(selection_.begin(), selection_.end(), std::back_inserter(newSelection),
        [&queriedName] (T* unit) { return unit->getName() == queriedName; });

    return UnitSelectionImpl<T>(newSelection);
}

template <class T>
UnitSelectionImpl<T> UnitSelectionImpl<T>::typeEqual(Type queriedType) const {
    std::vector<T*> newSelection;
    std::copy_if(selection_.begin(), selection_.end(), std::back_inserter(newSelection),
        [&queriedType] (T* unit) { return unit->getType() == queriedType; });

    return UnitSelectionImpl<T>(newSelection);
}

template <class T>
UnitSelectionImpl<T> UnitSelectionImpl<T>::tileEqual(const Tile& queriedTile) const {
    std::vector<T*> newSelection;
    std::copy_if(selection_.begin(), selection_.end(), std::back_inserter(newSelection),
        [&queriedTile] (T* unit) { return unit->getPosition() == queriedTile; });

    return UnitSelectionImpl<T>(newSelection);
}

template <class T>
UnitSelectionImpl<T> UnitSelectionImpl<T>::playerEqual(const players::Player* queriedPlayer) const {
    std::vector<T*> newSelection;
    std::copy_if(selection_.begin(), selection_.end(), std::back_inserter(newSelection),
        [&queriedPlayer] (T* unit) { return unit->getOwner() == queriedPlayer; });

    return UnitSelectionImpl<T>(newSelection);
}

template <class T>
UnitSelectionImpl<T> UnitSelectionImpl<T>::playerNotEqual(const players::Player* queriedPlayer) const {
    std::vector<T*> newSelection;
    std::copy_if(selection_.begin(), selection_.end(), std::back_inserter(newSelection),
        [&queriedPlayer] (T* unit) { return unit->getOwner() != queriedPlayer; });

    return UnitSelectionImpl<T>(newSelection);
}

template <class T>
typename UnitSelectionImpl<T>::iterator UnitSelectionImpl<T>::begin() {
    return iterator(this, 0);
}

template <class T>
typename UnitSelectionImpl<T>::iterator UnitSelectionImpl<T>::end() {
    return iterator(this, selection_.size());
}



template <class T>
UnitSelectionIterator<T>::UnitSelectionIterator(UnitSelectionImpl<T>* selection, size_t position)
    : selection_(selection), position_(position)
{ }

template <class T>
T& UnitSelectionIterator<T>::operator *() {
    return (*selection_)[position_];
}

template <class T>
bool operator == (const UnitSelectionIterator<T>& lhs, const UnitSelectionIterator<T>& rhs) {
    return (lhs.selection_ == rhs.selection_) && (lhs.position_ == rhs.position_);
}

template <class T>
bool operator != (const UnitSelectionIterator<T>& lhs, const UnitSelectionIterator<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
UnitSelectionIterator<T>& UnitSelectionIterator<T>::operator++() {
    ++position_;
    return *this;
}

template <class T>
UnitSelectionIterator<T> UnitSelectionIterator<T>::operator++(int) {
    UnitSelectionIterator<T> copy(*this);
    ++position_;
    return copy;
}


}  // namespace units

#endif  // UNITS_UNITSELECTION_HPP_
