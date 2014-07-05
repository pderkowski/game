/* Copyright 2014 <Piotr Derkowski> */

#ifndef MATCHER_HPP_
#define MATCHER_HPP_

#include <functional>
#include <vector>
#include <memory>
#include "Tile.hpp"
#include "TileEnums.hpp"

class Matcher {
public:
    typedef std::function<bool(std::shared_ptr<const Tile>)> Predicate;

    Matcher(Predicate predicate);
    virtual ~Matcher() { }

    virtual bool match(std::shared_ptr<const Tile> tile) const;

protected:
    Predicate predicate_;
};


class TileTypeMatcher : public Matcher {
public:
    TileTypeMatcher(tileenums::Type type);
    virtual ~TileTypeMatcher() { }
};


class NeighborTypesMatcher : public Matcher {
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

#endif  // MATCHER_HPP_
