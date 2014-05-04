/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include <vector>
#include "NoiseGenerator.hpp"
#include "noise/noise.h"
#include "noiseutils/noiseutils.h"

NoiseGenerator::NoiseGenerator(std::shared_ptr<std::default_random_engine> generator)
    : generator_(generator)
{ }

noise::utils::NoiseMap NoiseGenerator::generateNoiseMap(unsigned rows, unsigned columns,
        double scale) {
    noise::module::Perlin perlinModule;
    perlinModule.SetSeed((*generator_)());
    noise::module::ScaleBias scaledPerlinModule;
    scaledPerlinModule.SetSourceModule(0, perlinModule);
    scaledPerlinModule.SetBias(0);
    scaledPerlinModule.SetScale(scale);
    noise::utils::NoiseMap noiseMap;
    noise::utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(scaledPerlinModule);
    heightMapBuilder.SetDestNoiseMap(noiseMap);
    heightMapBuilder.SetDestSize(columns, rows);
    heightMapBuilder.SetBounds(0.0, columns / 32.0, 0.0, rows / 32.0);
    heightMapBuilder.Build();
    return noiseMap;
}
