#include "../include/CTriangle.h"
#include "../utils/Colors.h"
#include "../utils/HitTest.h"
#include <cmath>

CTriangle::CTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3) : m_p1(p1), m_p2(p2), m_p3(p3) {
    m_shape.setPointCount(3);
    m_shape.setPoint(0, sf::Vector2f(static_cast<float>(p1.x), static_cast<float>(p1.y)));
    m_shape.setPoint(1, sf::Vector2f(static_cast<float>(p2.x), static_cast<float>(p2.y)));
    m_shape.setPoint(2, sf::Vector2f(static_cast<float>(p3.x), static_cast<float>(p3.y)));
    m_shape.setFillColor(ShapeColors::TriangleFill());
    m_shape.setOutlineColor(ShapeColors::TriangleOutline());
    m_shape.setOutlineThickness(ShapeColors::OutlineThickness());
}

double CTriangle::GetArea() const {
    return std::abs(m_p1.x * (m_p2.y - m_p3.y) + m_p2.x * (m_p3.y - m_p1.y) + m_p3.x * (m_p1.y - m_p2.y)) / 2.0;
}

double CTriangle::GetPerimeter() const {
    auto distance = [](const CPoint& a, const CPoint& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    };
    return distance(m_p1, m_p2) + distance(m_p2, m_p3) + distance(m_p3, m_p1);
}

bool CTriangle::Contains(const sf::Vector2f& point) const {
    return HitTest::InTriangle(point, m_p1, m_p2, m_p3);
}

sf::Color CTriangle::GetDefaultOutlineColor() const {
    return ShapeColors::TriangleOutline();
}