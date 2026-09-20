#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "../utils/Config.h"

class IShape {
public:
    virtual ~IShape() = default;
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;

    virtual bool Contains(const sf::Vector2f& point) const = 0;
    virtual void SetSelected(bool selected) = 0;
    virtual void Move(float dx, float dy) = 0;

    std::string ToString() const {
        std::ostringstream oss;
        oss << GetTypePrefix()
            << Config::LABEL_SEPARATOR << Config::LABEL_PERIMETER << FormatNumber(GetPerimeter())
            << Config::VALUE_SEPARATOR << Config::LABEL_AREA      << FormatNumber(GetArea());
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
        oss << std::fixed << std::setprecision(Config::PRECISION) << value;
        return oss.str();
    }
};