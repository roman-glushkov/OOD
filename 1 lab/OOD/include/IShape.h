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
    
    // Template Method: общий алгоритм формирования строки
    std::string ToString() const {
        std::ostringstream oss;
        oss << GetTypePrefix() << ": P=" << FormatNumber(GetPerimeter())
            << "; S=" << FormatNumber(GetArea());
        return oss.str();
    }
    
protected:
    virtual std::string GetTypePrefix() const = 0;
    
private:
    static std::string FormatNumber(double value) {
        if (value == static_cast<int>(value)) {
            return std::to_string(static_cast<int>(value));
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << value;
        return oss.str();
    }
};