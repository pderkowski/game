/* Copyright 2014 <Piotr Derkowski> */

#ifndef NOISEGENERATOR_HPP_
#define NOISEGENERATOR_HPP_

#include <random>
#include <memory>
#include <vector>
#include "noiseutils/noiseutils.h"

class NoiseGenerator {
public:
    typedef std::vector<std::vector<double>> NoiseMatrix;

    explicit NoiseGenerator(std::shared_ptr<std::default_random_engine> generator);

    noise::utils::NoiseMap generateNoiseMap(unsigned rows, unsigned columns, double scale);

private:
    std::shared_ptr<std::default_random_engine> generator_;
};

#endif  // NOISEGENERATOR_HPP_
