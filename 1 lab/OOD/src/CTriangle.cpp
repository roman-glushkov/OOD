// CTriangle.cpp
#include "CTriangle.h"
#include <cmath>

CTriangle::CTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3, const sf::ConvexShape& shape)
    : m_p1(p1), m_p2(p2), m_p3(p3), m_shape(shape) {}

double CTriangle::GetArea() const {
    return std::abs(
        m_p1.x * (m_p2.y - m_p3.y) +
        m_p2.x * (m_p3.y - m_p1.y) +
        m_p3.x * (m_p1.y - m_p2.y)
    ) / 2.0;
}

double CTriangle::GetPerimeter() const {
    auto distance = [](const CPoint& a, const CPoint& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    };
    return distance(m_p1, m_p2) + distance(m_p2, m_p3) + distance(m_p3, m_p1);
}

void CTriangle::Draw(sf::RenderWindow& window) const {
    window.draw(m_shape); 
}