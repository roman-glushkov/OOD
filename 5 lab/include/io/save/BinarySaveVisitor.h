#pragma once
#include "io/save/IShapeSaveVisitor.h"
#include <fstream>

class BinarySaveVisitor : public IShapeSaveVisitor
{
public:
    explicit BinarySaveVisitor(std::ofstream& out);

    void Visit(const CTriangle& shape) override;
    void Visit(const CRectangle& shape) override;
    void Visit(const CCircle& shape) override;
    void Visit(const CompositeShape& shape) override;

private:
    std::ofstream& m_out;
};