/* Copyright 2014 <Piotr Derkowski> */

#ifndef HEIGHTMAP_HPP_
#define HEIGHTMAP_HPP_

#include <functional>
#include <tuple>
#include <vector>

class HeightMap {
public:
    HeightMap(unsigned rowsNo, unsigned columnsNo);

    const double& operator() (unsigned row, unsigned column) const;
    double& operator() (unsigned row, unsigned column);

    HeightMap& foreach(std::function<double(double)> transformation);

    unsigned getRowsNo() const;
    unsigned getColumnsNo() const;

    std::vector<std::tuple<unsigned, unsigned, double>> getListOfCells() const;

private:
    unsigned rowsNo_;
    unsigned columnsNo_;
    std::vector<std::vector<double>> map_;
};

#endif  // HEIGHTMAP_HPP_
