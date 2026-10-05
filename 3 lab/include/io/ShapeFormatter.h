#pragma once
#include "core/IShape.h"
#include <string>

class ShapeFormatter
{
public:
    static std::string ToString(const IShape& shape);

private:
    static std::string FormatNumber(double value);
};