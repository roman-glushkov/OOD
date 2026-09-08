// CRectangle.cpp
#include "CRectangle.h"
#include <cmath>

CRectangle::CRectangle(const CPoint& p1, const CPoint& p2, const sf::RectangleShape& shape)
    : m_p1(p1), m_p2(p2), m_shape(shape) {}

double CRectangle::GetArea() const {
    return std::abs((m_p2.x - m_p1.x) * (m_p2.y - m_p1.y));
}

double CRectangle::GetPerimeter() const {
    double width = std::abs(m_p2.x - m_p1.x);
    double height = std::abs(m_p2.y - m_p1.y);
    return 2.0 * (width + height);
}

void CRectangle::Draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
}