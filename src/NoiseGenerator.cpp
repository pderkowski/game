/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include <vector>
#include "NoiseGenerator.hpp"
#include "noise/noise.h"
#include "noiseutils/noiseutils.h"

NoiseGenerator::NoiseGenerator(std::shared_ptr<std::default_random_engine> generator)
    : generator_(generator)
{ }

noise::utils::NoiseMap NoiseGenerator::generateNoiseMap(unsigned rows, unsigned columns) {
    noise::module::Perlin noiseModule;
    noiseModule.SetSeed((*generator_)());
    noise::utils::NoiseMap noiseMap;
    noise::utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(noiseModule);
    heightMapBuilder.SetDestNoiseMap(noiseMap);
    heightMapBuilder.SetDestSize(columns, rows);
    heightMapBuilder.SetBounds(0.0, columns / 16.0, 0.0, rows / 16.0);
    heightMapBuilder.Build();
    return noiseMap;
}
