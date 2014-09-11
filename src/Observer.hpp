/* Copyright 2014 <Piotr Derkowski> */

#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_


template <class NotificationType>
class Observer {
public:
    virtual ~Observer() { }

    virtual void onNotify(const NotificationType& notification) = 0;
};


#endif  // OBSERVER_HPP_
