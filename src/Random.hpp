/* Copyright 2014 <Piotr Derkowski> */

#ifndef RANDOM_HPP_
#define RANDOM_HPP_


#include <random>


class Random {
public:
    static void initialize(unsigned seed);

    static unsigned getNumber();

private:
    Random() = delete;

private:
    static std::default_random_engine generator;

};


#endif  // RANDOM_HPP_
