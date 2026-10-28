#pragma once
#include <string>
#include <vector>
#include <memory>
#include "core/IShape.h"

class IShapeSaveStrategy
{
public:
    virtual ~IShapeSaveStrategy() = default;

    virtual void Save(const std::vector<std::unique_ptr<IShape>>& shapes, const std::string& path) const = 0;
};