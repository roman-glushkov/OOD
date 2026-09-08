// IShape.h
#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>

class IShape {
public:
    virtual ~IShape() = default;
    
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;
    std::string ToString() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2)
            << GetTypePrefix() << ": P=" 
            << GetPerimeter() 
            << "; S=" 
            << GetArea();
        return oss.str();
    }
    
protected:
    virtual std::string GetTypePrefix() const = 0;
};