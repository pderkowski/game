/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_NOISEGENERATOR_HPP_
#define MAP_NOISEGENERATOR_HPP_

#include "HeightMap.hpp"


namespace map {


class NoiseGenerator {
public:
    static HeightMap generateHeightMap(unsigned rows, unsigned columns, unsigned seed,
        double frequency = 1.0, double persistence = 0.5);
};


}  // namespace map

#endif  // MAP_NOISEGENERATOR_HPP_
