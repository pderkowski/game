/* Copyright 2014 <Piotr Derkowski> */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <stdexcept>
#include "SFML/Graphics.hpp"
#include "TextureSet.hpp"
#include "Utils.hpp"

template <class T>
class Layer : public sf::Drawable {
public:
    explicit Layer(const TextureSet<T>& textureSet);
    virtual ~Layer() { }

    void draw(sf::RenderTarget& target,
        sf::RenderStates states = sf::RenderStates::Default) const;

    void add(const T&, const sf::Vector2f& center);
    void remove(const T&, const sf::Vector2f& center);

private:
    struct VertexPosition {
        size_t start;
        size_t size;
    };

    struct Key {
        Key(const T& t, const sf::Vector2f& center);
        bool operator < (const Key& rhs) const;

        std::pair<const T*, sf::Vector2f> key;
    };

private:
    void removeVertices(const VertexPosition& position);
    void updatePositions(const VertexPosition& position);

    TextureSet<T> textureSet_;
    sf::VertexArray vertices_;
    std::map<Key, VertexPosition> positions_;
};

template <class T>
Layer<T>::Layer(const TextureSet<T>& textureSet)
    : textureSet_(textureSet),
    vertices_(sf::Quads)
{ }

template <class T>
void Layer<T>::add(const T& t, const sf::Vector2f& center)
{
    const auto key = Key(t, center);
    if (positions_.find(key) == positions_.end()) {
        size_t sizeBefore = vertices_.getVertexCount();

        auto vertices = textureSet_.getVertices(t);
        for (unsigned i = 0; i < vertices.getVertexCount(); ++i) {
            vertices[i].position += (center - sf::Vector2f(48, 24));
            vertices_.append(vertices[i]);
        }

        size_t sizeAfter = vertices_.getVertexCount();

        if (sizeAfter > sizeBefore) {

            positions_.insert(std::make_pair(key, VertexPosition{ sizeBefore, sizeAfter - sizeBefore }));
        }
    } else {
        throw std::runtime_error("Trying to add an item that has already been inserted.");
    }
}

template <class T>
void Layer<T>::remove(const T& t, const sf::Vector2f& center) {
    const auto key = Key(t, center);
    if (positions_.find(key) != positions_.end()) {
        auto position = positions_.at(key);
        removeVertices(position);
        positions_.erase(key);
        updatePositions(position);
    }
}

template <class T>
void Layer<T>::removeVertices(const VertexPosition& position) {
    for (size_t pos = position.start + position.size; pos != vertices_.getVertexCount(); ++pos) {
        vertices_[pos - position.size] = vertices_[pos];
    }

    vertices_.resize(vertices_.getVertexCount() - position.size);
}

template <class T>
void Layer<T>::updatePositions(const VertexPosition& position) {
    for (auto& t_position : positions_) {
        if (t_position.second.start > position.start)
            t_position.second.start -= position.size;
    }
}

template <class T>
void Layer<T>::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.texture = textureSet_.getActualTexture().get();
    target.draw(vertices_, states);
}



template <class T>
Layer<T>::Key::Key(const T& t, const sf::Vector2f& center)
    : key(std::make_pair(&t, center))
{ }

template <class T>
bool Layer<T>::Key::operator < (const Key& rhs) const {
    using utils::operator <;

    return (key.first < rhs.key.first) || (key.first == rhs.key.first && key.second < rhs.key.second);
}


#endif  // LAYER_HPP_







