#pragma once
#include <memory>
#include "IShape.h"
#include "ShapeParser.h"

class ShapeFactory {
public:
    // создаём фигуру по данным из парсера
    static std::unique_ptr<IShape> Create(const ShapeParser::ParsedData& data);
};