#pragma once
#include "IShape.h"
#include <vector>
#include <memory>

class CompositeShape : public IShape 
{
public:
    void Add(std::unique_ptr<IShape> shape) 
    {
        m_children.push_back(std::move(shape));
    }

    std::vector<std::unique_ptr<IShape>> Release() 
    {
        return std::move(m_children);
    }

    std::size_t Size() const 
    { 
        return m_children.size(); 
    }

    void Draw(sf::RenderWindow& window) const override 
    {
        for (const auto& child : m_children) 
        {
            child->Draw(window);
        }
    }

    bool Contains(const sf::Vector2f& point) const override 
    {
        for (const auto& child : m_children) 
        {
            if (child->Contains(point)) return true;
        }
        return false;
    }

    void SetSelected(bool selected) override 
    {
        for (const auto& child : m_children) 
        {
            child->SetSelected(selected);
        }
    }

    void Move(float dx, float dy) override 
    {
        for (const auto& child : m_children) 
        {
            child->Move(dx, dy);
        }
    }

    double GetArea() const override 
    {
        double sum = 0.0;
        for (const auto& child : m_children) sum += child->GetArea();
        return sum;
    }

    double GetPerimeter() const override 
    {
        double sum = 0.0;
        for (const auto& child : m_children) sum += child->GetPerimeter();
        return sum;
    }

    std::string GetTypePrefix() const override { return "COMPOSITE"; }

private:
    std::vector<std::unique_ptr<IShape>> m_children;
};