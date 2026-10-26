#include "memento/CanvasMemento.h"

CanvasMemento::CanvasMemento(std::vector<std::unique_ptr<IShape>> shapes)
    : m_shapes(std::move(shapes))
{
}

std::vector<std::unique_ptr<IShape>> CanvasMemento::GetShapesCopy() const
{
    std::vector<std::unique_ptr<IShape>> copy;
    copy.reserve(m_shapes.size());
    for (const auto& shape : m_shapes)
    {
        copy.push_back(shape->Clone());
    }
    return copy;
}