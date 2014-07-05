/* Copyright 2014 <Piotr Derkowski> */

#ifndef MATCHER_HPP_
#define MATCHER_HPP_

#include <functional>
#include <vector>
#include <memory>
#include "Tile.hpp"
#include "TileEnums.hpp"

template <class T>
class Matcher {
public:
    typedef std::function<bool(const T&)> Predicate;

    Matcher(Predicate predicate);
    virtual ~Matcher() { }

    virtual bool match(const T&) const;

protected:
    Predicate predicate_;
};


class TileTypeMatcher : public Matcher<Tile> {
public:
    TileTypeMatcher(tileenums::Type type);
    virtual ~TileTypeMatcher() { }
};


class NeighborTypesMatcher : public Matcher<Tile> {
public:
    enum NeighborType {
        Any,
        Same,
        Different
    };

    typedef std::vector<NeighborType> NeighborTypes;

    NeighborTypesMatcher(tileenums::Type type, const NeighborTypes& neighborTypes);
    virtual ~NeighborTypesMatcher() { }
};


template <class T>
Matcher<T>::Matcher(Predicate predicate)
    : predicate_(predicate)
{ }


template <class T>
bool Matcher<T>::match(const T& t) const {
    return predicate_(t);
}

#endif  // MATCHER_HPP_
