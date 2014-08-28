/* Copyright 2014 <Piotr Derkowski> */

#ifndef GLOBAL_RANDOM_HPP_
#define GLOBAL_RANDOM_HPP_


#include <random>


namespace global {


class Random {
public:
    static void initialize(unsigned seed);

    static unsigned getNumber();

private:
    Random() = delete;

private:
    static std::default_random_engine generator;

};


}  // namespace global


#endif  // GLOBAL_RANDOM_HPP_
