/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include <vector>
#include "NoiseGenerator.hpp"
#include "HeightMap.hpp"
#include "noise/noise.h"
#include "noiseutils/noiseutils.h"

NoiseGenerator::NoiseGenerator(std::shared_ptr<std::default_random_engine> generator)
    : generator_(generator)
{ }

HeightMap NoiseGenerator::generateHeightMap(unsigned rows, unsigned columns) {
    noise::module::Perlin perlinModule;
    perlinModule.SetSeed((*generator_)());
    noise::utils::NoiseMap noiseMap;
    noise::utils::NoiseMapBuilderPlane noiseMapBuilder;
    noiseMapBuilder.SetSourceModule(perlinModule);
    noiseMapBuilder.SetDestNoiseMap(noiseMap);
    noiseMapBuilder.SetDestSize(columns, rows);
    noiseMapBuilder.SetBounds(0.0, columns / 16.0, 0.0, rows / 16.0);
    noiseMapBuilder.Build();

    HeightMap result(rows, columns);
    for (unsigned r = 0; r < rows; ++r) {
        for (unsigned c = 0; c < columns; ++c) {
            result[r][c] = noiseMap.GetValue(c, r);
        }
    }

    return result;
}
