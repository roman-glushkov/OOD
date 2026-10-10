#include "commands/ModifyShapesCommand.h"

#include <utility>

ModifyShapesCommand::ModifyShapesCommand(const std::vector<IShape*>& shapes, Action action): m_shapes(shapes), m_action(std::move(action)) {}

void ModifyShapesCommand::Execute()
{
    if (!m_action)
    {
        return;
    }

    for (IShape* shape : m_shapes)
    {
        if (shape)
        {
            m_action(shape);
        }
    }
}
