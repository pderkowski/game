/* Copyright 2014 <Piotr Derkowski> */

#ifndef MATCHER_HPP_
#define MATCHER_HPP_

#include <functional>
#include <vector>
#include <memory>
#include "Tile.hpp"

class Matcher {
public:
    typedef std::function<bool(std::shared_ptr<const Tile>, const std::vector<std::shared_ptr<const Tile>>&)> Predicate;

    Matcher(Predicate predicate);
    virtual ~Matcher() { }

    virtual bool match(std::shared_ptr<const Tile> tile,
        const std::vector<std::shared_ptr<const Tile>>& neighbors) const;

protected:
    Predicate predicate_;
};


class TileMatcher : public Matcher {
public:
    TileMatcher(std::function<bool(std::shared_ptr<const Tile>)> predicate);
    virtual ~TileMatcher() { }
};


class TileTypeMatcher : public Matcher {
public:
    TileTypeMatcher(Tile::Type type);
    TileTypeMatcher(const TileTypeMatcher&) = delete;
    TileTypeMatcher(const TileTypeMatcher&&) = delete;

    virtual ~TileTypeMatcher() { }

private:
    Tile::Type type_;
};


class NeighborTypesMatcher : public Matcher {
public:
    enum NeighborType {
        Any,
        Same,
        Different
    };

    typedef std::vector<NeighborType> NeighborTypes;

    NeighborTypesMatcher(Tile::Type type, const NeighborTypes& neighborTypes);
    NeighborTypesMatcher(const NeighborTypesMatcher&) = delete;
    NeighborTypesMatcher(const NeighborTypesMatcher&&) = delete;

    virtual ~NeighborTypesMatcher() { }

private:
    Tile::Type type_;
    NeighborTypes neighborTypes_;
};

#endif  // MATCHER_HPP_
