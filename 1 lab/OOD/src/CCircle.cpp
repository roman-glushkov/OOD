// CCircle.cpp
#include "CCircle.h"
#include <cmath>
#include <sstream>

const double PI = 3.141592653589793;

CCircle::CCircle(const CPoint& center, double radius)
    : m_center(center), m_radius(radius) {}

double CCircle::GetArea() const {
    return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const {
    return 2.0 * PI * m_radius;
}

std::string CCircle::ToString() const {
    std::ostringstream oss;
    oss << "CIRCLE: P=" << GetPerimeter() << "; S=" << GetArea();
    return oss.str();
}

void CCircle::Draw(sf::RenderWindow& window) const {
    if (!m_initialized) {
        m_sfmlShape.setRadius(static_cast<float>(m_radius));
        // SFML 3.0: setPosition принимает Vector2f
        m_sfmlShape.setPosition({
            static_cast<float>(m_center.x - m_radius),
            static_cast<float>(m_center.y - m_radius)
        });
        m_sfmlShape.setPointCount(100);
        
        m_sfmlShape.setFillColor(sf::Color(100, 200, 255, 150));
        m_sfmlShape.setOutlineColor(sf::Color::Black);
        m_sfmlShape.setOutlineThickness(2.0f);
        
        m_initialized = true;
    }
    
    window.draw(m_sfmlShape);
}