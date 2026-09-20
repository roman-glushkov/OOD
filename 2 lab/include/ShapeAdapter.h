#pragma once
#include "IShape.h"
#include "../utils/Colors.h"
#include <SFML/Graphics.hpp>

template <typename TSfmlShape> // тип SFML-фигуры
class ShapeAdapter : public IShape {
public:
    // рисуем фигуру в окне
    void Draw(sf::RenderWindow& window) const override { 
        window.draw(m_shape);
    }

    // выделяем фигуру
    void SetSelected(bool selected) override {
        if (selected) {
            m_shape.setOutlineColor(sf::Color::Green);
            m_shape.setOutlineThickness(ShapeColors::OutlineThickness() * 2.0f);
        } else {
            m_shape.setOutlineColor(GetDefaultOutlineColor());
            m_shape.setOutlineThickness(ShapeColors::OutlineThickness());
        }
    }

protected:
    TSfmlShape m_shape;
    virtual sf::Color GetDefaultOutlineColor() const = 0;
};