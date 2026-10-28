#pragma once
#include "adapter/ShapeAdapter.h"
#include "core/CPoint.h"
#include "utils/Config.h"

class CRectangle : public ShapeAdapter<sf::RectangleShape>
{
public:
    CRectangle(const CPoint& p1, const CPoint& p2);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string GetTypePrefix() const override { return Config::TYPE_RECTANGLE; }

    bool Contains(const sf::Vector2f& point) const override;
    void Move(float dx, float dy) override;
    void Accept(IShapeVisitor& visitor) override;
    void Accept(IShapeSaveVisitor& visitor) override;  

    const CPoint& GetP1() const { return m_p1; }   
    const CPoint& GetP2() const { return m_p2; }  

protected:
    std::unique_ptr<IShape> CloneImpl() const override;

private:
    CPoint m_p1, m_p2;
};