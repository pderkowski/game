/* Copyright 2014 <Piotr Derkowski> */

#ifndef CONVERTER_HPP_
#define CONVERTER_HPP_

#include <functional>

template<class T, class U>
class Converter {
public:
    Converter(std::function<U(const T&)> conversion,
        std::function<T(const U&)> inversion);

    U convert(const T& value) const;
    T invert(const U& value) const;

private:
    std::function<U(const T&)> conversion_;
    std::function<T(const U&)> inversion_;
};

template<class T, class U>
Converter<T, U>::Converter(std::function<U(const T&)> conversion,
        std::function<T(const U&)> inversion)
    : conversion_(conversion), inversion_(inversion)
{ }

template<class T, class U>
U Converter<T, U>::convert(const T& value) const {
    return conversion_(value);
}

template<class T, class U>
T Converter<T, U>::invert(const U& value) const {
    return inversion_(value);
}

#endif  // CONVERTER_HPP_
