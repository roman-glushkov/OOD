#pragma once
#include "io/load/ShapeData.h"
#include "core/IShape.h"
#include <memory>

// Director: знает, в каком порядке вызывать шаги Builder'а
class ShapeBuildDirector
{
public:
    std::unique_ptr<IShape> Build(const ShapeData& data) const;
};