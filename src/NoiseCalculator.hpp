/* Copyright 2014 <Piotr Derkowski> */

#ifndef NOISECALCULATOR_HPP_
#define NOISECALCULATOR_HPP_

#include <random>
#include <array>

class NoiseCalculator {
public:
    NoiseCalculator(unsigned grain, unsigned seed);

    double calculateNoise(unsigned row, unsigned column) const;

private:
    typedef std::pair<double, double> Vector2D;
    typedef std::array<Vector2D, 4> FourVectors2D;

    Vector2D normalize(const Vector2D& unnormalized) const;
    FourVectors2D calculateGridPoints(const Vector2D& point) const;
    FourVectors2D calculateShiftVectors(const FourVectors2D& gridPoints,
        const Vector2D& point) const;
    FourVectors2D generateNoiseVectors(const FourVectors2D& gridPoints) const;
    Vector2D generateNoiseVector(const Vector2D& gridPoint) const;
    unsigned hash(const Vector2D& gridPoint, unsigned seed) const;
    std::array<double, 4> calculateDotProducts(const FourVectors2D& lhs,
        const FourVectors2D& rhs) const;
    double calculateWeight(double distance) const;
    double calculateWeightedSum(double lhs, double rhs, double weight) const;

    unsigned grain_;
    unsigned seed_;
    mutable std::default_random_engine generator_;
};

#endif  // NOISECALCULATOR_HPP_
