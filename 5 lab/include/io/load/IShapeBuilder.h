#pragma once
#include "core/CPoint.h"
#include <memory>
#include <string>
#include "core/IShape.h"

// Builder: пошагово собирает фигуру из ShapeData
class IShapeBuilder
{
public:
    virtual ~IShapeBuilder() = default;

    virtual void Reset() = 0;
    virtual void SetType(const std::string& type) = 0;
    virtual void AddPoint(const CPoint& p) = 0;
    virtual void SetRadius(double radius) = 0;
    virtual std::unique_ptr<IShape> GetResult() = 0;
};