#include "CRectangle.h"
#include "../utils/Colors.h"
#include <cmath>

CRectangle::CRectangle(const CPoint& p1, const CPoint& p2)
    : m_p1(p1), m_p2(p2) {
    float width = static_cast<float>(std::abs(p2.x - p1.x));
    float height = static_cast<float>(std::abs(p2.y - p1.y));
    
    m_shape.setSize(sf::Vector2f(width, height));
    m_shape.setPosition({
        static_cast<float>(std::min(p1.x, p2.x)),
        static_cast<float>(std::min(p1.y, p2.y))
    });
    
    m_shape.setFillColor(ShapeColors::RectangleFill());
    m_shape.setOutlineColor(ShapeColors::RectangleOutline());
    m_shape.setOutlineThickness(ShapeColors::OutlineThickness());
}

double CRectangle::GetArea() const {
    return std::abs((m_p2.x - m_p1.x) * (m_p2.y - m_p1.y));
}

double CRectangle::GetPerimeter() const {
    double width = std::abs(m_p2.x - m_p1.x);
    double height = std::abs(m_p2.y - m_p1.y);
    return 2.0 * (width + height);
}