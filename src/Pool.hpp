/* Copyright 2014 <Piotr Derkowski> */

#ifndef POOL_HPP_
#define POOL_HPP_

#include <random>
#include <memory>
#include <utility>
#include <map>
#include <vector>

template <class T>
class Pool {
public:
    explicit Pool(std::shared_ptr<std::default_random_engine> generator);

    void insert(T* key, unsigned weight);
    T* getRandom() const;
    void remove(T* key);
    bool contains(T* key) const;
    unsigned getWeight(T* key) const;
    void setWeight(T* key, unsigned weight);
    bool isEmpty() const;
    std::vector<T*> toVector() const;

private:
    unsigned totalWeight_;
    std::map<T*, unsigned> weights_;

    std::shared_ptr<std::default_random_engine> generator_;


    typedef std::pair<typename decltype(weights_)::iterator, bool> InsertionResultType;

    bool wasInserted(const InsertionResultType& result) const;
    T* findRange(unsigned point) const;
};

template <class T>
Pool<T>::Pool(std::shared_ptr<std::default_random_engine> generator)
    : totalWeight_(0),
    weights_(),
    generator_(generator)
{ }

template <class T>
inline void Pool<T>::insert(T* key, unsigned weight) {
    if (wasInserted(weights_.insert({ key, weight }))) {
        totalWeight_ += weight;
    }
}

template <class T>
inline bool Pool<T>::wasInserted(const InsertionResultType& insertionResult) const {
    return insertionResult.second;
}

template <class T>
inline T* Pool<T>::getRandom() const {
    unsigned point = (*generator_)() % totalWeight_;
    return findRange(point);
}

template <class T>
inline T* Pool<T>::findRange(unsigned point) const {
    auto rangeIt = weights_.begin();
    for (unsigned sum = rangeIt->second; sum < point; ++rangeIt, sum += rangeIt->second)
    { }

    return rangeIt->first;
}

template <class T>
inline void Pool<T>::remove(T* key) {
    if (contains(key)) {
        unsigned removedWeight = getWeight(key);
        weights_.erase(key);
        totalWeight_ -= removedWeight;
    }
}

template <class T>
inline bool Pool<T>::contains(T* key) const {
    return weights_.find(key) != weights_.end();
}

template <class T>
inline unsigned Pool<T>::getWeight(T* key) const {
    return weights_.at(key);
}

template <class T>
inline void Pool<T>::setWeight(T* key, unsigned weight) {
    remove(key);
    insert(key, weight);
}

template <class T>
inline bool Pool<T>::isEmpty() const {
    return weights_.empty();
}

template <class T>
inline std::vector<T*> Pool<T>::toVector() const {
    std::vector<T*> res;

    for (auto keyAndWeight : weights_) {
        res.push_back(keyAndWeight.first);
    }

    return res;
}


namespace utils {

template <class T>
void increaseWeight(Pool<T>& pool, T* key, unsigned initialWeight = 1,
        unsigned increaseFactor = 2) {
    if (pool.contains(key)) {
        unsigned weight = pool.getWeight(key);
        pool.setWeight(key, weight * increaseFactor);
    } else {
        pool.insert(key, initialWeight);
    }
}

}  // namespace utils

#endif  // POOL_HPP_


