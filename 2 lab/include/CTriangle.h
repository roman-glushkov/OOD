#pragma once
#include "ShapeAdapter.h"
#include "CPoint.h"

class CTriangle : public ShapeAdapter<sf::ConvexShape> {
public:
    CTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    
protected:
    std::string GetTypePrefix() const override { return "TRIANGLE"; }
    
private:
    CPoint m_p1, m_p2, m_p3;
};