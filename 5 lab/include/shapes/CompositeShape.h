#pragma once
#include "core/IShape.h"
#include <vector>
#include <memory>

class CompositeShape : public IShape 
{
public:
    void Add(std::unique_ptr<IShape> shape);
    std::vector<std::unique_ptr<IShape>> Release();

    void Draw(sf::RenderWindow& window) const override;
    bool Contains(const sf::Vector2f& point) const override;
    void Move(float dx, float dy) override;
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string GetTypePrefix() const override;
    sf::FloatRect GetBounds() const override;

    void SetOutlineColor(sf::Color color) override;
    void SetFillColor(sf::Color color) override;
    void SetOutlineThickness(float thickness) override;
    sf::Color GetOutlineColor() const override;
    sf::Color GetFillColor() const override;
    float GetOutlineThickness() const override;

    void Accept(IShapeVisitor& visitor) override;
    void Accept(IShapeSaveVisitor& visitor) override; 

    const std::vector<std::unique_ptr<IShape>>& GetChildren() const { return m_children; }  

    std::unique_ptr<IShape> Clone() const override;

private:
    std::vector<std::unique_ptr<IShape>> m_children;
};