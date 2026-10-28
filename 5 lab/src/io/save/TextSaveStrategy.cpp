#include "io/save/TextSaveStrategy.h"
#include "io/save/TextSaveVisitor.h"
#include "utils/Config.h"
#include <fstream>
#include <stdexcept>

void TextSaveStrategy::Save(const std::vector<std::unique_ptr<IShape>>& shapes,
                            const std::string& path) const
{
    std::ofstream out(path);
    if (!out)
    {
        throw std::runtime_error(Config::MSG_SAVE_OPEN_FAILED_TEXT + path);
    }

    TextSaveVisitor visitor(out);
    for (const auto& shape : shapes)
    {
        shape->Accept(visitor);
    }
}