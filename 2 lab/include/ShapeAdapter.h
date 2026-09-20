#pragma once
#include "IShape.h"
#include "../utils/Colors.h"
#include "../utils/Config.h"
#include <SFML/Graphics.hpp>

template <typename TSfmlShape>
class ShapeAdapter : public IShape {
public:
    void Draw(sf::RenderWindow& window) const override {
        window.draw(m_shape);
    }

    void SetSelected(bool selected) override {
        if (selected) {
            m_shape.setOutlineColor(ShapeColors::SelectedOutline());
            m_shape.setOutlineThickness(ShapeColors::OutlineThickness() * Config::SELECTED_THICKNESS_FACTOR);
        } else {
            m_shape.setOutlineColor(GetDefaultOutlineColor());
            m_shape.setOutlineThickness(ShapeColors::OutlineThickness());
        }
    }

    void Move(float dx, float dy) override {
        m_shape.move({dx, dy});
    }

protected:
    TSfmlShape m_shape;
    virtual sf::Color GetDefaultOutlineColor() const = 0;
};