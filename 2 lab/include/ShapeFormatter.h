#pragma once
#include "IShape.h"
#include "../utils/Config.h"
#include <string>
#include <sstream>
#include <iomanip>

class ShapeFormatter
{
public:
    static std::string ToString(const IShape& shape)
    {
        std::ostringstream oss;
        oss << shape.GetTypePrefix()
            << Config::LABEL_SEPARATOR << Config::LABEL_PERIMETER << FormatNumber(shape.GetPerimeter())
            << Config::VALUE_SEPARATOR << Config::LABEL_AREA      << FormatNumber(shape.GetArea());
        return oss.str();
    }

private:
    static std::string FormatNumber(double value)
    {
        if (value == static_cast<int>(value))
        {
            return std::to_string(static_cast<int>(value));
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(Config::PRECISION) << value;
        return oss.str();
    }
};