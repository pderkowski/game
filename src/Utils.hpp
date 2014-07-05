/* Copyright 2014 <Piotr Derkowski> */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "SFML/System/Vector2.hpp"

namespace utils {

inline int positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

inline bool operator <(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
    return (lhs.x < rhs.x) || (lhs.x == rhs.x && lhs.y < rhs.y);
}

}

#endif  // UTILS_HPP_
