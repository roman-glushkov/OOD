#pragma once
#include "core/IShape.h"
#include "utils/Colors.h"
#include "utils/Config.h"
#include <SFML/Graphics.hpp>

template <typename TSfmlShape>
class ShapeAdapter : public IShape 
{
public:
    void Draw(sf::RenderWindow& window) const override 
    {
        window.draw(m_shape);
    }

    void SetSelected(bool) override {}

    void Move(float dx, float dy) override 
    {
        m_shape.move({dx, dy});
    }

    sf::FloatRect GetBounds() const override 
    {
        return m_shape.getGlobalBounds();
    }

    void SetOutlineColor(sf::Color color) override 
    {
        m_shape.setOutlineColor(color);
    }

    void SetFillColor(sf::Color color) override 
    {
        m_shape.setFillColor(color);
    }

    void SetOutlineThickness(float thickness) override 
    {
        m_shape.setOutlineThickness(thickness);
    }

    sf::Color GetOutlineColor() const override { return m_shape.getOutlineColor(); }
    sf::Color GetFillColor() const override    { return m_shape.getFillColor(); }
    float GetOutlineThickness() const override { return m_shape.getOutlineThickness(); }

protected:
    TSfmlShape m_shape;
};