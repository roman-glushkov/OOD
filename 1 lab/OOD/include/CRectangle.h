// CRectangle.h
#pragma once
#include "IShape.h"
#include "CPoint.h"
#include <SFML/Graphics.hpp>

class CRectangle : public IShape {
public:
    CRectangle(const CPoint& p1, const CPoint& p2);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    void Draw(sf::RenderWindow& window) const override;
    
private:
    CPoint m_p1, m_p2;
    mutable sf::RectangleShape m_sfmlShape;
    mutable bool m_initialized = false;
};