#pragma once
#include "io/save/IShapeSaveStrategy.h"
#include <memory>
#include <vector>
#include <string>

class ShapeSaver
{
public:
    explicit ShapeSaver(std::unique_ptr<IShapeSaveStrategy> strategy);

    void SetStrategy(std::unique_ptr<IShapeSaveStrategy> strategy);

    void Save(const std::vector<std::unique_ptr<IShape>>& shapes,
              const std::string& path) const;

private:
    std::unique_ptr<IShapeSaveStrategy> m_strategy;
};