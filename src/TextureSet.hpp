/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURESET_HPP_
#define TEXTURESET_HPP_

#include <vector>
#include <memory>
#include <utility>
#include "SFML/Graphics.hpp"
#include "Matcher.hpp"

template <class T>
class TextureSet {
public:
    TextureSet(std::shared_ptr<const sf::Texture> texture);

    void add(std::shared_ptr<const Matcher<T>> textureMatcher, const sf::VertexArray& vertices);
    sf::VertexArray getVertices(const T&) const;

    std::shared_ptr<const sf::Texture> getActualTexture() const;

private:
    std::shared_ptr<const sf::Texture> texture_;
    std::vector<std::pair<std::shared_ptr<const Matcher<T>>, sf::VertexArray>> textureMatchers_;
};


template <class T>
TextureSet<T>::TextureSet(std::shared_ptr<const sf::Texture> texture)
    : texture_(texture)
{ }

template <class T>
void TextureSet<T>::add(std::shared_ptr<const Matcher<T>> textureMatcher, const sf::VertexArray& vertices) {
    textureMatchers_.push_back(std::make_pair(textureMatcher, vertices));
}

template <class T>
sf::VertexArray TextureSet<T>::getVertices(const T& t) const
{
    sf::VertexArray matchedVertices;
    for (const auto& matcher_vertices : textureMatchers_) {
        if (matcher_vertices.first->match(t)) {
            for (unsigned i = 0; i < matcher_vertices.second.getVertexCount(); ++i) {
                matchedVertices.append(matcher_vertices.second[i]);
            }
        }
    }
    return matchedVertices;
}

template <class T>
std::shared_ptr<const sf::Texture> TextureSet<T>::getActualTexture() const {
    return texture_;
}

#endif  // TEXTURESET_HPP_
