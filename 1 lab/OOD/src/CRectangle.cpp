// CRectangle.cpp
#include "CRectangle.h"
#include <cmath>
#include <sstream>

CRectangle::CRectangle(const CPoint& p1, const CPoint& p2) : m_p1(p1), m_p2(p2) {}

double CRectangle::GetArea() const {
    return std::abs((m_p2.x - m_p1.x) * (m_p2.y - m_p1.y));
}

double CRectangle::GetPerimeter() const {
    double width = std::abs(m_p2.x - m_p1.x);
    double height = std::abs(m_p2.y - m_p1.y);
    return 2.0 * (width + height);
}

std::string CRectangle::ToString() const {
    std::ostringstream oss;
    oss << "RECTANGLE: P=" << GetPerimeter() << "; S=" << GetArea();
    return oss.str();
}

void CRectangle::Draw(sf::RenderWindow& window) const {
    if (!m_initialized) {
        float width = static_cast<float>(std::abs(m_p2.x - m_p1.x));
        float height = static_cast<float>(std::abs(m_p2.y - m_p1.y));
        
        m_sfmlShape.setSize(sf::Vector2f(width, height));
        // SFML 3.0: setPosition принимает Vector2f
        m_sfmlShape.setPosition({
            static_cast<float>(std::min(m_p1.x, m_p2.x)),
            static_cast<float>(std::min(m_p1.y, m_p2.y))
        });
        
        m_sfmlShape.setFillColor(sf::Color(255, 100, 100, 150));
        m_sfmlShape.setOutlineColor(sf::Color::Black);
        m_sfmlShape.setOutlineThickness(2.0f);
        
        m_initialized = true;
    }
    
    window.draw(m_sfmlShape);
}