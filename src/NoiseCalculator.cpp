/* Copyright 2014 <Piotr Derkowski> */

#include <random>
#include <cmath>
#include <utility>
#include <functional>
#include <array>
#include <limits>
#include <iostream>
#include "NoiseCalculator.hpp"

namespace utils {
    double dotProduct(const std::pair<double, double>& lhs, const std::pair<double, double>& rhs) {
        return lhs.first * rhs.first + lhs.second * rhs.second;
    }

    template <class T>
    void print(const T& container) {
        for (const auto& v : container) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    template <class T, class U>
    std::ostream& operator << (std::ostream& out, const std::pair<T, U>& p) {
        return out << "(" << p.first << ", " << p.second << ")";
    }

}  // namespace utils

NoiseCalculator::NoiseCalculator(unsigned grain, unsigned seed)
    : grain_(grain), seed_(seed)
{ }

double NoiseCalculator::calculateNoise(unsigned row, unsigned column) const {
    using namespace utils;

    Vector2D point = normalize(Vector2D(column + 0.5, row + 0.5));

    auto gridPoints = calculateGridPoints(point);
    auto shiftVectors = calculateShiftVectors(gridPoints, point);
    auto noiseVectors = generateNoiseVectors(gridPoints);

    auto dotProducts = calculateDotProducts(noiseVectors, shiftVectors);
    auto topWeightedSum = calculateWeightedSum(dotProducts[0], dotProducts[1],
        calculateWeight(fabs(shiftVectors[0].first)));
    auto bottomWeightedSum = calculateWeightedSum(dotProducts[2], dotProducts[3],
        calculateWeight(fabs(shiftVectors[2].first)));

    return calculateWeightedSum(topWeightedSum, bottomWeightedSum,
        calculateWeight(fabs(shiftVectors[0].second)));
}

NoiseCalculator::Vector2D NoiseCalculator::normalize(const Vector2D& unnormalized) const {
    return Vector2D(unnormalized.first / grain_, unnormalized.second / grain_);
}

NoiseCalculator::FourVectors2D NoiseCalculator::calculateGridPoints(const Vector2D& point) const {
    FourVectors2D points;
    points[0] = { floor(point.first), floor(point.second) };
    points[1] = { floor(point.first) + 1, floor(point.second) };
    points[2] = { floor(point.first), floor(point.second) + 1 };
    points[3] = { floor(point.first) + 1, floor(point.second) + 1 };
    return points;
}

NoiseCalculator::FourVectors2D NoiseCalculator::calculateShiftVectors(
        const FourVectors2D& gridPoints,
        const Vector2D& point) const {
    FourVectors2D shiftVectors;
    for (unsigned i = 0; i < shiftVectors.size(); ++i) {
        shiftVectors[i]
            = { point.first - gridPoints[i].first, point.second - gridPoints[i].second };
    }

    return shiftVectors;
}

NoiseCalculator::FourVectors2D NoiseCalculator::generateNoiseVectors(
        const FourVectors2D& gridPoints) const {
    FourVectors2D noiseVectors;
    for (unsigned i = 0; i < gridPoints.size(); ++i) {
        noiseVectors[i] = generateNoiseVector(gridPoints[i]);
    }

    return noiseVectors;
}

NoiseCalculator::Vector2D NoiseCalculator::generateNoiseVector(const Vector2D& gridPoint) const {
    Vector2D noiseVector;
    generator_.seed(hash(gridPoint, seed_));
    // generate random number in range [0..1]:
    double randomNumber
        = std::generate_canonical<double, std::numeric_limits<double>::digits>(generator_);
    // scale it to [0..2*pi]
    double angle = 2 * M_PI * randomNumber;
    noiseVector.first = sin(angle);
    noiseVector.second = cos(angle);
    return noiseVector;
}

unsigned NoiseCalculator::hash(const Vector2D& gridPoint, unsigned seed) const {
    unsigned long long x = static_cast<unsigned>(gridPoint.first);
    unsigned long long y = static_cast<unsigned>(gridPoint.second);
    std::hash<unsigned long long> ullHash;
    return ullHash(ullHash(seed * (x + 1)) * (y + 1));
}

std::array<double, 4> NoiseCalculator::calculateDotProducts(const FourVectors2D& lhs,
        const FourVectors2D& rhs) const {
    std::array<double, 4> dotProducts;
    for (unsigned i = 0; i < lhs.size(); ++i) {
        dotProducts[i] = utils::dotProduct(lhs[i], rhs[i]);
    }

    return dotProducts;
}

double NoiseCalculator::calculateWeight(double distance) const {
    double relativeDistance = distance / grain_;
    return 3 * pow(relativeDistance, 2) - 2 * pow(relativeDistance, 3);
}

double NoiseCalculator::calculateWeightedSum(double lhs, double rhs, double weight) const {
    return lhs + weight * (rhs - lhs);
}
