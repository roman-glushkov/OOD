#include "shapes/CompositeShape.h"
#include "utils/Config.h"

void CompositeShape::Add(std::unique_ptr<IShape> shape) 
{
    m_children.push_back(std::move(shape));
}

std::vector<std::unique_ptr<IShape>> CompositeShape::Release() 
{
    return std::move(m_children);
}

void CompositeShape::Draw(sf::RenderWindow& window) const 
{
    for (const auto& child : m_children) 
    {
        child->Draw(window);
    }
}

bool CompositeShape::Contains(const sf::Vector2f& point) const 
{
    for (const auto& child : m_children) 
    {
        if (child->Contains(point)) return true;
    }
    return false;
}

void CompositeShape::SetSelected(bool selected) 
{
    for (const auto& child : m_children) 
    {
        child->SetSelected(selected);
    }
}

void CompositeShape::Move(float dx, float dy) 
{
    for (const auto& child : m_children) 
    {
        child->Move(dx, dy);
    }
}

double CompositeShape::GetArea() const 
{
    double sum = Config::ZERO_SUM;
    for (const auto& child : m_children) sum += child->GetArea();
    return sum;
}

double CompositeShape::GetPerimeter() const 
{
    double sum = Config::ZERO_SUM;
    for (const auto& child : m_children) sum += child->GetPerimeter();
    return sum;
}

std::string CompositeShape::GetTypePrefix() const 
{
    return Config::TYPE_COMPOSITE;
}

sf::FloatRect CompositeShape::GetBounds() const 
{
    if (m_children.empty()) return sf::FloatRect();

    sf::FloatRect result = m_children[0]->GetBounds();
    for (std::size_t i = 1; i < m_children.size(); ++i) 
    {
        sf::FloatRect b = m_children[i]->GetBounds();

        float minX = std::min(result.position.x, b.position.x);
        float minY = std::min(result.position.y, b.position.y);
        float maxX = std::max(result.position.x + result.size.x, b.position.x + b.size.x);
        float maxY = std::max(result.position.y + result.size.y, b.position.y + b.size.y);

        result = sf::FloatRect({minX, minY}, {maxX - minX, maxY - minY});
    }
    return result;
}