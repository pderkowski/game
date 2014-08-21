/* Copyright 2014 <Piotr Derkowski> */

#include <functional>
#include "SFML/System/Clock.hpp"
#include "Timer.hpp"


Timer::Timer(int interval, std::function<void()> callback)
    : interval_(interval), callback_(callback)
{ }

bool Timer::elapsed() const {
    return clock_.getElapsedTime().asMilliseconds() > interval_;
}

void Timer::executeCallback() {
    callback_();
    clock_.restart();
}
