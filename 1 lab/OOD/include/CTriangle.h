// CTriangle.h
#pragma once
#include "IShape.h"
#include "CPoint.h"
#include <SFML/Graphics.hpp>

class CTriangle : public IShape {
public:
    CTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    void Draw(sf::RenderWindow& window) const override;
    
private:
    CPoint m_p1, m_p2, m_p3;
    mutable sf::ConvexShape m_sfmlShape;
    mutable bool m_initialized = false;
};