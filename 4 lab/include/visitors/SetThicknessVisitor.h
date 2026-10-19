#pragma once
#include "visitors/IShapeVisitor.h"
#include "shapes/CTriangle.h"
#include "shapes/CRectangle.h"
#include "shapes/CCircle.h"
#include "shapes/CompositeShape.h"

// Visitor для изменения толщины обводки
class SetThicknessVisitor : public IShapeVisitor
{
public:
    explicit SetThicknessVisitor(float thickness) : m_thickness(thickness) {}

    void Visit(CTriangle& shape) override
    {
        shape.SetOutlineThickness(m_thickness);
    }

    void Visit(CRectangle& shape) override
    {
        shape.SetOutlineThickness(m_thickness);
    }

    void Visit(CCircle& shape) override
    {
        shape.SetOutlineThickness(m_thickness);
    }

    void Visit(CompositeShape& shape) override
    {
        shape.SetOutlineThickness(m_thickness);
    }

private:
    float m_thickness;
};