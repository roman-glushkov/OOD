#pragma once
#include "visitors/IShapeVisitor.h"
#include "shapes/CTriangle.h"
#include "shapes/CRectangle.h"
#include "shapes/CCircle.h"
#include "shapes/CompositeShape.h"
#include <SFML/Graphics.hpp>

// Visitor для изменения цвета заливки
class SetFillColorVisitor : public IShapeVisitor
{
public:
    explicit SetFillColorVisitor(sf::Color color) : m_color(color) {}

    void Visit(CTriangle& shape) override
    {
        shape.SetFillColor(m_color);
    }

    void Visit(CRectangle& shape) override
    {
        shape.SetFillColor(m_color);
    }

    void Visit(CCircle& shape) override
    {
        shape.SetFillColor(m_color);
    }

    void Visit(CompositeShape& shape) override
    {
        shape.SetFillColor(m_color);
    }

private:
    sf::Color m_color;
};