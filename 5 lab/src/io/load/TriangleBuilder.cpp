#include "io/load/TriangleBuilder.h"
#include "shapes/CTriangle.h"
#include "utils/Config.h"
#include <stdexcept>

void TriangleBuilder::Reset()
{
    m_points.clear();
}

void TriangleBuilder::SetType(const std::string& type)
{
    if (type != Config::TYPE_TRIANGLE)
    {
        throw std::runtime_error(Config::MSG_TRIANGLE_BUILDER_TYPE + type);
    }
}

void TriangleBuilder::AddPoint(const CPoint& p)
{
    m_points.push_back(p);
}

void TriangleBuilder::SetRadius(double radius)
{
    // треугольнику радиус не нужен
}

std::unique_ptr<IShape> TriangleBuilder::GetResult()
{
    if (m_points.size() != Config::TRIANGLE_POINTS_REQUIRED)
    {
        throw std::runtime_error(Config::MSG_TRIANGLE_BUILDER_POINTS);
    }
    auto result = std::make_unique<CTriangle>(m_points[0], m_points[1], m_points[2]);
    m_points.clear();
    return result;
}