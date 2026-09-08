// ShapeAdapter.h
#pragma once
#include "IShape.h"
#include <SFML/Graphics.hpp>

template <typename TSfmlShape>
class ShapeAdapter : public IShape {
public:
    void Draw(sf::RenderWindow& window) const override {
        window.draw(m_shape);
    }
    
protected:
    TSfmlShape m_shape;
};