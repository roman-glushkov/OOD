#include "../include/ShapeFactory.h"
#include "../include/CTriangle.h"
#include "../include/CRectangle.h"
#include "../include/CCircle.h"

// создаём конкретную фигуру по данным из парсера
std::unique_ptr<IShape> ShapeFactory::Create(const ShapeParser::ParsedData& data) {
    if (data.type == "TRIANGLE") {
        return std::make_unique<CTriangle>(data.points[0], data.points[1], data.points[2]);
    }
    else if (data.type == "RECTANGLE") {
        return std::make_unique<CRectangle>(data.points[0], data.points[1]);
    }
    else if (data.type == "CIRCLE") {
        return std::make_unique<CCircle>(data.points[0], data.radius);
    }
    return nullptr;
}