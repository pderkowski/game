/* Copyright 2014 <Piotr Derkowski> */

#ifndef MISCELLANEOUSENUMS_HPP_
#define MISCELLANEOUSENUMS_HPP_

#include <string>
#include <stdexcept>
#include "boost/functional/hash.hpp"

namespace miscellaneous {

enum class Type {
    Source,
    Destination,
};

}  // namespace miscellaneous


namespace std {

template <>
struct hash<miscellaneous::Type>
{
    std::size_t operator()(const miscellaneous::Type& type) const
    {
        std::size_t seed = 0;

        static std::hash<int> typeHasher;
        boost::hash_combine(seed, typeHasher(static_cast<int>(type)));

        return seed;
    }
};

}  // namespace std

#endif  // MISCELLANEOUSENUMS_HPP_
