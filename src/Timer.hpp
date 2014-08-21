/* Copyright 2014 <Piotr Derkowski> */

#ifndef TIMER_HPP_
#define TIMER_HPP_


#include <functional>
#include "SFML/System/Clock.hpp"


class Timer {
public:
    Timer(int interval, std::function<void()> callback);

    bool elapsed() const;
    void executeCallback();

private:
    sf::Clock clock_;

    int interval_;
    std::function<void()> callback_;

};

#endif  // TIMER_HPP_
