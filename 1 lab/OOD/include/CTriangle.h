// CTriangle.h
#pragma once
#include "IShape.h"
#include "CPoint.h"
#include <SFML/Graphics.hpp>

class CTriangle : public IShape {
public:
    CTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3, const sf::ConvexShape& shape);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    void Draw(sf::RenderWindow& window) const override;
    
protected:
    std::string GetTypePrefix() const override { return "TRIANGLE"; }
    
private:
    CPoint m_p1, m_p2, m_p3;
    sf::ConvexShape m_shape;
};