#pragma once
#include "io/save/IShapeSaveStrategy.h"

class TextSaveStrategy : public IShapeSaveStrategy
{
public:
    void Save(const std::vector<std::unique_ptr<IShape>>& shapes,
              const std::string& path) const override;
};