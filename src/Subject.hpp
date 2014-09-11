/* Copyright 2014 <Piotr Derkowski> */

#ifndef SUBJECT_HPP_
#define SUBJECT_HPP_

#include <vector>
#include "Observer.hpp"


template <class NotificationType>
class Subject {
public:
    virtual ~Subject() { }

    void addObserver(Observer<NotificationType>* observer);

protected:
    void notify(const NotificationType& notification) const;

private:
    std::vector<Observer<NotificationType>*> observers_;
};


template <class NotificationType>
void Subject<NotificationType>::notify(const NotificationType& notification) const {
    for (Observer<NotificationType>* observer : observers_) {
        observer->onNotify(notification);
    }
}

template <class NotificationType>
void Subject<NotificationType>::addObserver(Observer<NotificationType>* observer) {
    observers_.push_back(observer);
}


#endif  // SUBJECT_HPP_
