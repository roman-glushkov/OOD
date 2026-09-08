// CCircle.cpp
#include "CCircle.h"
#include <cmath>

const double PI = 3.141592653589793;

CCircle::CCircle(const CPoint& center, double radius, const sf::CircleShape& shape)
    : m_center(center), m_radius(radius), m_shape(shape) {}

double CCircle::GetArea() const {
    return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const {
    return 2.0 * PI * m_radius;
}

void CCircle::Draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
}