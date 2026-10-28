#pragma once

class CTriangle;
class CRectangle;
class CCircle;
class CompositeShape;

class IShapeSaveVisitor
{
public:
    virtual ~IShapeSaveVisitor() = default;

    virtual void Visit(const CTriangle& shape) = 0;
    virtual void Visit(const CRectangle& shape) = 0;
    virtual void Visit(const CCircle& shape) = 0;
    virtual void Visit(const CompositeShape& shape) = 0;
};