// CRectangle.h
#pragma once
#include "IShape.h"
#include "CPoint.h"
#include <SFML/Graphics.hpp>

class CRectangle : public IShape {
public:
    CRectangle(const CPoint& p1, const CPoint& p2, const sf::RectangleShape& shape);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    void Draw(sf::RenderWindow& window) const override;
    
protected:
    std::string GetTypePrefix() const override { return "RECTANGLE"; }
    
private:
    CPoint m_p1, m_p2;
    sf::RectangleShape m_shape;
};