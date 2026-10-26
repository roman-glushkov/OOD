#pragma once
#include <vector>
#include <memory>
#include "core/IShape.h"

class CanvasMemento 
{
public:
    explicit CanvasMemento(std::vector<std::unique_ptr<IShape>> shapes);
    std::vector<std::unique_ptr<IShape>> GetShapesCopy() const; 

private:
    std::vector<std::unique_ptr<IShape>> m_shapes;
};