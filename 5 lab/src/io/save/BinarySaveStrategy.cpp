#include "io/save/BinarySaveStrategy.h"
#include "io/save/BinarySaveVisitor.h"
#include "utils/Config.h"
#include <fstream>
#include <stdexcept>
#include <cstdint>

void BinarySaveStrategy::Save(const std::vector<std::unique_ptr<IShape>>& shapes,
                              const std::string& path) const
{
    std::ofstream out(path, std::ios::binary);
    if (!out)
    {
        throw std::runtime_error(Config::MSG_SAVE_OPEN_FAILED_BINARY + path);
    }

    std::uint32_t count = static_cast<std::uint32_t>(shapes.size());
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    BinarySaveVisitor visitor(out);
    for (const auto& shape : shapes)
    {
        shape->Accept(visitor);
    }
}