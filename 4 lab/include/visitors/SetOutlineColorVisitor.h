#pragma once
#include "visitors/IShapeVisitor.h"
#include "shapes/CTriangle.h"
#include "shapes/CRectangle.h"
#include "shapes/CCircle.h"
#include "shapes/CompositeShape.h"
#include <SFML/Graphics.hpp>

// Visitor для изменения цвета обводки
class SetOutlineColorVisitor : public IShapeVisitor
{
public:
    explicit SetOutlineColorVisitor(sf::Color color) : m_color(color) {}

    void Visit(CTriangle& shape) override
    {
        shape.SetOutlineColor(m_color);
    }

    void Visit(CRectangle& shape) override
    {
        shape.SetOutlineColor(m_color);
    }

    void Visit(CCircle& shape) override
    {
        shape.SetOutlineColor(m_color);
    }

    void Visit(CompositeShape& shape) override
    {
        shape.SetOutlineColor(m_color);
    }

private:
    sf::Color m_color;
};