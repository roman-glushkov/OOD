#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>

class IShape {
public:
    // виртуальный деструктор со стандартной реализацией
    virtual ~IShape() = default;
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;

    // попадание точки внутрь фигуры
    virtual bool Contains(const sf::Vector2f& point) const = 0;

    // включить/выключить визуальное выделение
    virtual void SetSelected(bool selected) = 0;

    // формируем строку с информацией о фигуре
    std::string ToString() const {
        std::ostringstream oss;
        oss << GetTypePrefix()
            << ": P=" << FormatNumber(GetPerimeter())
            << "; S=" << FormatNumber(GetArea());
        return oss.str();
    }

protected:
    // возвращаем название фигуры
    virtual std::string GetTypePrefix() const = 0;

private:
    // форматируем вывод
    static std::string FormatNumber(double value) { 
        if (value == static_cast<int>(value)) {
            return std::to_string(static_cast<int>(value));
        }

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << value;
        return oss.str();
    }
};