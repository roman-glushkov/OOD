#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include "../utils/Config.h"

class IShape {
public:
    // виртуальный деструктор со стандартной реализацией
    virtual ~IShape() = default;
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;

    // формируем строку с информацией о фигуре
    std::string ToString() const {
        std::ostringstream oss;
        oss << GetTypePrefix()
            << Config::LABEL_SEPARATOR << Config::LABEL_PERIMETER << FormatNumber(GetPerimeter())
            << Config::VALUE_SEPARATOR << Config::LABEL_AREA      << FormatNumber(GetArea());
        return oss.str();
    }

protected:
    // возвращаем название фигуры
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