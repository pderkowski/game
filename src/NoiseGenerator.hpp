/* Copyright 2014 <Piotr Derkowski> */

#ifndef NOISEGENERATOR_HPP_
#define NOISEGENERATOR_HPP_

#include <random>
#include <memory>
#include <vector>

class NoiseGenerator {
public:
    typedef std::vector<std::vector<double>> NoiseMatrix;

    explicit NoiseGenerator(std::shared_ptr<std::default_random_engine> generator);

    NoiseMatrix generateNoiseMatrix(unsigned rows, unsigned columns);
    void scale(NoiseMatrix& matrix, int min, int max) const;

private:
    std::shared_ptr<std::default_random_engine> generator_;
};

#endif  // NOISEGENERATOR_HPP_
