#include "io/ShapeFormatter.h"
#include "utils/Config.h"
#include <sstream>
#include <iomanip>

std::string ShapeFormatter::ToString(const IShape& shape)
{
    std::ostringstream oss;
    oss << shape.GetTypePrefix()
        << Config::LABEL_SEPARATOR << Config::LABEL_PERIMETER << FormatNumber(shape.GetPerimeter())
        << Config::VALUE_SEPARATOR << Config::LABEL_AREA      << FormatNumber(shape.GetArea());
    return oss.str();
}

std::string ShapeFormatter::FormatNumber(double value)
{
    if (value == static_cast<int>(value))
    {
        return std::to_string(static_cast<int>(value));
    }
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(Config::PRECISION) << value;
    return oss.str();
}