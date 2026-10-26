#pragma once

class CTriangle;
class CRectangle;
class CCircle;
class CompositeShape;

class IShapeVisitor
{
public:
    virtual ~IShapeVisitor() = default;

    // методы Visit для каждой фигуры
    virtual void Visit(CTriangle& shape) = 0;
    virtual void Visit(CRectangle& shape) = 0;
    virtual void Visit(CCircle& shape) = 0;
    virtual void Visit(CompositeShape& shape) = 0;
};