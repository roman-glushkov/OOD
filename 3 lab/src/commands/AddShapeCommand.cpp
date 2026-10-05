#include "commands/AddShapeCommand.h"

#include <utility>

AddShapeCommand::AddShapeCommand(std::vector<std::unique_ptr<IShape>>& shapes,
                                  std::unique_ptr<IShape> newShape)
    : m_shapes(shapes), m_newShape(std::move(newShape)) {}

void AddShapeCommand::Execute() 
{
    m_shapes.push_back(std::move(m_newShape));
}
