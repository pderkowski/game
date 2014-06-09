/* Copyright 2014 <Piotr Derkowski> */

#ifndef NOISEGENERATOR_HPP_
#define NOISEGENERATOR_HPP_

#include "HeightMap.hpp"

class NoiseGenerator {
public:
    static HeightMap generateHeightMap(unsigned rows, unsigned columns, unsigned seed,
        double frequency = 1.0, double persistence = 0.5);
};

#endif  // NOISEGENERATOR_HPP_
