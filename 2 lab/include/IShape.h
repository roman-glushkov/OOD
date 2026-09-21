#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class IShape
{
public:
    virtual ~IShape() = default;

    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;

    virtual bool Contains(const sf::Vector2f& point) const = 0;
    virtual void SetSelected(bool selected) = 0;
    virtual void Move(float dx, float dy) = 0;

    virtual std::string GetTypePrefix() const = 0;
};