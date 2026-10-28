#pragma once
#include "io/save/IShapeSaveVisitor.h"
#include <ostream>

// Visitor для текстового сохранения в формате, совместимом с ShapeParser
class TextSaveVisitor : public IShapeSaveVisitor
{
public:
    explicit TextSaveVisitor(std::ostream& out);

    void Visit(const CTriangle& shape) override;
    void Visit(const CRectangle& shape) override;
    void Visit(const CCircle& shape) override;
    void Visit(const CompositeShape& shape) override;

private:
    std::ostream& m_out;
};