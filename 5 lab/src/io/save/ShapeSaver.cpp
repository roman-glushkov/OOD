#include "io/save/ShapeSaver.h"
#include "utils/Config.h"
#include <stdexcept>
#include <utility>

ShapeSaver::ShapeSaver(std::unique_ptr<IShapeSaveStrategy> strategy)
    : m_strategy(std::move(strategy))
{
    if (!m_strategy)
    {
        throw std::invalid_argument(Config::MSG_SAVER_NULL_STRATEGY);
    }
}

void ShapeSaver::SetStrategy(std::unique_ptr<IShapeSaveStrategy> strategy)
{
    if (!strategy)
    {
        throw std::invalid_argument(Config::MSG_SAVER_NULL_STRATEGY);
    }
    m_strategy = std::move(strategy);
}

void ShapeSaver::Save(const std::vector<std::unique_ptr<IShape>>& shapes,
                      const std::string& path) const
{
    m_strategy->Save(shapes, path);
}