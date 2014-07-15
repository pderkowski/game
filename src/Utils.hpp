/* Copyright 2014 <Piotr Derkowski> */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <functional>
#include "boost/functional/hash.hpp"
#include "SFML/System/Vector2.hpp"

namespace utils {

inline int positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

inline bool operator <(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
    return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}

}  // namespace utils


namespace std {

template <>
struct hash<sf::Vector2f>
{
    std::size_t operator()(const sf::Vector2f& vec) const
    {
        std::size_t seed = 0;

        static std::hash<float> hasher;

        boost::hash_combine(seed, hasher(vec.x));
        boost::hash_combine(seed, hasher(vec.y));

        return seed;
    }
};

}  // namespace std

#endif  // UTILS_HPP_
