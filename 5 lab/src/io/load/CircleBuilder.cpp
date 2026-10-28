#include "io/load/CircleBuilder.h"
#include "shapes/CCircle.h"
#include "utils/Config.h"
#include <stdexcept>

void CircleBuilder::Reset()
{
    m_center = CPoint();
    m_radius = 0.0;
    m_hasCenter = false;
}

void CircleBuilder::SetType(const std::string& type)
{
    if (type != Config::TYPE_CIRCLE)
    {
        throw std::runtime_error(Config::MSG_CIRCLE_BUILDER_TYPE + type);
    }
}

void CircleBuilder::AddPoint(const CPoint& p)
{
    m_center = p;
    m_hasCenter = true;
}

void CircleBuilder::SetRadius(double radius)
{
    m_radius = radius;
}

std::unique_ptr<IShape> CircleBuilder::GetResult()
{
    if (!m_hasCenter)
    {
        throw std::runtime_error(Config::MSG_CIRCLE_BUILDER_NO_CENTER);
    }
    auto result = std::make_unique<CCircle>(m_center, m_radius);
    m_center = CPoint();
    m_radius = 0.0;
    m_hasCenter = false;
    return result;
}