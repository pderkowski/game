/* Copyright 2014 <Piotr Derkowski> */

#ifndef NOISEGENERATOR_HPP_
#define NOISEGENERATOR_HPP_

#include "HeightMap.hpp"

class NoiseGenerator {
public:
    static HeightMap generateHeightMap(unsigned rows, unsigned columns, unsigned seed,
        double persistence);
};

#endif  // NOISEGENERATOR_HPP_
