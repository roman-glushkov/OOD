#pragma once
#include "ShapeAdapter.h"
#include "CPoint.h"

class CRectangle : public ShapeAdapter<sf::RectangleShape> {
public:
    CRectangle(const CPoint& p1, const CPoint& p2);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    
protected:
    std::string GetTypePrefix() const override { return "RECTANGLE"; }
    
private:
    CPoint m_p1, m_p2;
};