/* Copyright 2014 <Piotr Derkowski> */

#include "boost/optional.hpp"

template<class T>
class Attribute;

template<class T>
bool operator == (const Attribute<T>& lhs, const Attribute<T>& rhs) {
    return (lhs && rhs && (*lhs == *rhs)) || (!lhs && !rhs);
}


template<class T>
class Attribute {
public:
    void enable();
    void disable();
    operator bool() const;

    const T& operator *() const;
    T& operator *();

    const T* operator ->() const;
    T* operator ->();

private:
    friend bool operator == <>(const Attribute<T>& lhs, const Attribute<T>& rhs);

    boost::optional<T> data_;
};


template<class T>
void Attribute<T>::enable() {
    if (!data_)
        data_ = T();
}

template<class T>
void Attribute<T>::disable() {
    data_ = boost::optional<T>();
}

template<class T>
Attribute<T>::operator bool() const {
    return data_;
}

template<class T>
const T& Attribute<T>::operator *() const {
    return *data_;
}

template<class T>
T& Attribute<T>::operator *() {
    return *data_;
}

template<class T>
const T* Attribute<T>::operator ->() const {
    return data_.get_ptr();
}

template<class T>
T* Attribute<T>::operator ->() {
    return data_.get_ptr();
}

