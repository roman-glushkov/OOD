#pragma once
#include <vector>
#include <memory>
#include "core/IShape.h"

class CanvasMemento
{
public:
    explicit CanvasMemento(std::vector<std::unique_ptr<IShape>> shapes)
        : m_shapes(std::move(shapes)) {}

    std::vector<std::unique_ptr<IShape>> GetShapesCopy() const
    {
        std::vector<std::unique_ptr<IShape>> copy;
        copy.reserve(m_shapes.size());
        for (const auto& shape : m_shapes)
        {
            copy.push_back(shape->Clone());
        }
        return copy;
    }

private:
    std::vector<std::unique_ptr<IShape>> m_shapes;
};