#include "io/save/BinarySaveVisitor.h"
#include "shapes/CTriangle.h"
#include "shapes/CRectangle.h"
#include "shapes/CCircle.h"
#include "shapes/CompositeShape.h"
#include "utils/Config.h"
#include <cstdint>

namespace
{
    template <typename T>
    void Write(std::ofstream& out, const T& value)
    {
        out.write(reinterpret_cast<const char*>(&value), sizeof(T));
    }
}

BinarySaveVisitor::BinarySaveVisitor(std::ofstream& out)
    : m_out(out)
{
}

void BinarySaveVisitor::Visit(const CTriangle& shape)
{
    Write(m_out, Config::BINARY_TYPE_TRIANGLE);
    Write(m_out, shape.GetP1().x); Write(m_out, shape.GetP1().y);
    Write(m_out, shape.GetP2().x); Write(m_out, shape.GetP2().y);
    Write(m_out, shape.GetP3().x); Write(m_out, shape.GetP3().y);
}

void BinarySaveVisitor::Visit(const CRectangle& shape)
{
    Write(m_out, Config::BINARY_TYPE_RECTANGLE);
    Write(m_out, shape.GetP1().x); Write(m_out, shape.GetP1().y);
    Write(m_out, shape.GetP2().x); Write(m_out, shape.GetP2().y);
}

void BinarySaveVisitor::Visit(const CCircle& shape)
{
    Write(m_out, Config::BINARY_TYPE_CIRCLE);
    Write(m_out, shape.GetCenter().x); Write(m_out, shape.GetCenter().y);
    Write(m_out, shape.GetRadius());
}

void BinarySaveVisitor::Visit(const CompositeShape& shape)
{
    Write(m_out, Config::BINARY_TYPE_COMPOSITE);
    std::uint32_t count = static_cast<std::uint32_t>(shape.GetChildren().size());
    Write(m_out, count);
    for (const auto& child : shape.GetChildren())
    {
        child->Accept(*this);
    }
}