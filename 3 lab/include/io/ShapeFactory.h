#pragma once
#include <memory>
#include "core/IShape.h"
#include "io/ShapeParser.h"

class ShapeFactory 
{
public:
    static std::unique_ptr<IShape> Create(const ShapeParser::ParsedData& data);
};
