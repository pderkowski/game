/* Copyright 2014 <Piotr Derkowski> */

#ifndef HEIGHTMAP_HPP_
#define HEIGHTMAP_HPP_

#include <vector>

class HeightMap {
public:
    HeightMap(unsigned rowsNo, unsigned columnsNo);

    const std::vector<double>& operator[] (unsigned row) const;
    std::vector<double>& operator[] (unsigned row);

    void scale(double factor);
    void rise(double delta);

    unsigned getRowsNo() const;
    unsigned getColumnsNo() const;
private:
    unsigned rowsNo_;
    unsigned columnsNo_;
    std::vector<std::vector<double>> map_;
};

#endif  // HEIGHTMAP_HPP_
