// CTriangle.cpp
#include "CTriangle.h"
#include <cmath>
#include <sstream>

CTriangle::CTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3)
    : m_p1(p1), m_p2(p2), m_p3(p3) {}

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

std::string CTriangle::ToString() const {
    std::ostringstream oss;
    oss << "TRIANGLE: P=" << GetPerimeter() << "; S=" << GetArea();
    return oss.str();
}

void CTriangle::Draw(sf::RenderWindow& window) const {
    if (!m_initialized) {
        m_sfmlShape.setPointCount(3);
        m_sfmlShape.setPoint(0, sf::Vector2f(static_cast<float>(m_p1.x), static_cast<float>(m_p1.y)));
        m_sfmlShape.setPoint(1, sf::Vector2f(static_cast<float>(m_p2.x), static_cast<float>(m_p2.y)));
        m_sfmlShape.setPoint(2, sf::Vector2f(static_cast<float>(m_p3.x), static_cast<float>(m_p3.y)));
        
        m_sfmlShape.setFillColor(sf::Color(100, 255, 100, 150));
        m_sfmlShape.setOutlineColor(sf::Color::Black);
        m_sfmlShape.setOutlineThickness(2.0f);
        
        m_initialized = true;
    }
    
    window.draw(m_sfmlShape);
}