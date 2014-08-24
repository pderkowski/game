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

enum class Flag {
    Blue,
    Red
};

}  // namespace miscellaneous


namespace std {

template <>
struct hash<miscellaneous::Type>
{
    std::size_t operator()(const miscellaneous::Type& type) const
    {
        static std::hash<int> typeHasher;
        return typeHasher(static_cast<int>(type));
    }
};

template <>
struct hash<miscellaneous::Flag>
{
    std::size_t operator()(const miscellaneous::Flag& flag) const
    {
        static std::hash<int> typeHasher;
        return typeHasher(static_cast<int>(flag));
    }
};

}  // namespace std

#endif  // MISCELLANEOUSENUMS_HPP_
