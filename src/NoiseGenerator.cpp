/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include "NoiseGenerator.hpp"
#include "HeightMap.hpp"
#include "noise/noise.h"
#include "noiseutils/noiseutils.h"
#include "Coordinates.hpp"
#include "Utils.hpp"

HeightMap NoiseGenerator::generateHeightMap(unsigned rows, unsigned columns, unsigned seed) {
    noise::module::Perlin perlinModule;
    perlinModule.SetSeed(seed);
    perlinModule.SetPersistence(0.5);
    noise::utils::NoiseMap noiseMap;
    noise::utils::NoiseMapBuilderCylinder noiseMapBuilder;
    noiseMapBuilder.SetSourceModule(perlinModule);
    noiseMapBuilder.SetDestNoiseMap(noiseMap);
    noiseMapBuilder.SetDestSize(2 * columns, rows);
    noiseMapBuilder.SetBounds(-180.0, 180.0, 0.0, rows / 40.0);
    noiseMapBuilder.Build();

    HeightMap result(rows, columns);
    for (unsigned r = 0; r < rows; ++r) {
        for (unsigned c = 0; c < columns; ++c) {
            auto p = IntIsoPoint(c, r).toCartesian();
            result(r, c) = noiseMap.GetValue(::utils::positiveModulo(p.x, 2 * columns), p.y);
        }
    }

    return result;
}
