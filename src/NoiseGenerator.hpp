/* Copyright 2014 <Piotr Derkowski> */

#ifndef NOISEGENERATOR_HPP_
#define NOISEGENERATOR_HPP_

#include <random>
#include <memory>
#include <vector>
#include "HeightMap.hpp"

class NoiseGenerator {
public:
    explicit NoiseGenerator(std::shared_ptr<std::default_random_engine> generator);

    HeightMap generateHeightMap(unsigned rows, unsigned columns);

private:
    std::shared_ptr<std::default_random_engine> generator_;
};

#endif  // NOISEGENERATOR_HPP_
