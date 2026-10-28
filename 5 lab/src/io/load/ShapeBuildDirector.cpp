#include "io/load/ShapeBuildDirector.h"
#include "io/load/TriangleBuilder.h"
#include "io/load/RectangleBuilder.h"
#include "io/load/CircleBuilder.h"
#include "shapes/CompositeShape.h"
#include "utils/Config.h"
#include <stdexcept>

std::unique_ptr<IShape> ShapeBuildDirector::Build(const ShapeData& data) const
{
    if (data.type == Config::TYPE_TRIANGLE)
    {
        TriangleBuilder builder;
        builder.Reset();
        builder.SetType(data.type);
        for (const auto& p : data.points) builder.AddPoint(p);
        return builder.GetResult();
    }
    if (data.type == Config::TYPE_RECTANGLE)
    {
        RectangleBuilder builder;
        builder.Reset();
        builder.SetType(data.type);
        for (const auto& p : data.points) builder.AddPoint(p);
        return builder.GetResult();
    }
    if (data.type == Config::TYPE_CIRCLE)
    {
        CircleBuilder builder;
        builder.Reset();
        builder.SetType(data.type);
        if (!data.points.empty()) builder.AddPoint(data.points[0]);
        builder.SetRadius(data.radius);
        return builder.GetResult();
    }
    if (data.type == Config::TYPE_COMPOSITE)
    {
        auto composite = std::make_unique<CompositeShape>();
        for (const auto& childData : data.children)
        {
            composite->Add(Build(childData));
        }
        return composite;
    }
    throw std::runtime_error(Config::MSG_DIRECTOR_UNKNOWN_TYPE + data.type);
}