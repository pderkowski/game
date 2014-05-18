/* Copyright 2014 <Piotr Derkowski> */

#ifndef UTILS_HPP_
#define UTILS_HPP_

namespace utils {

inline int positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

}

#endif  // UTILS_HPP_
