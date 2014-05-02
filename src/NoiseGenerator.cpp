/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <memory>
#include <vector>
#include "NoiseGenerator.hpp"
#include "NoiseCalculator.hpp"

NoiseGenerator::NoiseGenerator(std::shared_ptr<std::default_random_engine> generator)
    : generator_(generator)
{ }

NoiseGenerator::NoiseMatrix NoiseGenerator::generateNoiseMatrix(unsigned rows, unsigned columns) {
    const unsigned grain = 5;
    NoiseCalculator calculator(grain, (*generator_)());

    NoiseMatrix noiseMatrix(rows, std::vector<double>(columns, 0));
    for (unsigned row = 0; row < noiseMatrix.size(); ++row) {
        for (unsigned column = 0; column < noiseMatrix[row].size(); ++column) {
            noiseMatrix[row][column] = calculator.calculateNoise(row, column);
        }
    }

    return noiseMatrix;
}

void NoiseGenerator::scale(NoiseMatrix& matrix, int min, int max) const {
    int difference = max - min;

    for (auto& row : matrix) {
        for (auto& cell : row) {
            cell = cell * difference + min;
        }
    }
}
