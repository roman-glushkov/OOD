// ShapeFactory.h
#pragma once
#include <memory>
#include "IShape.h"
#include "ShapeParser.h"

class ShapeFactory {
public:
    static std::unique_ptr<IShape> Create(const ShapeParser::ParsedData& data);
};