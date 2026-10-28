#include "io/load/RectangleBuilder.h"
#include "shapes/CRectangle.h"
#include "utils/Config.h"
#include <stdexcept>

void RectangleBuilder::Reset()
{
    m_points.clear();
}

void RectangleBuilder::SetType(const std::string& type)
{
    if (type != Config::TYPE_RECTANGLE)
    {
        throw std::runtime_error(Config::MSG_RECTANGLE_BUILDER_TYPE + type);
    }
}

void RectangleBuilder::AddPoint(const CPoint& p)
{
    m_points.push_back(p);
}

void RectangleBuilder::SetRadius(double radius)
{
    // прямоугольнику радиус не нужен
}

std::unique_ptr<IShape> RectangleBuilder::GetResult()
{
    if (m_points.size() != Config::RECTANGLE_POINTS_REQUIRED)
    {
        throw std::runtime_error(Config::MSG_RECTANGLE_BUILDER_POINTS);
    }
    auto result = std::make_unique<CRectangle>(m_points[0], m_points[1]);
    m_points.clear();
    return result;
}