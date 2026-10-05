#pragma once

#include "commands/ICommand.h"
#include "core/IShape.h"

#include <functional>
#include <vector>

class ModifyShapesCommand : public ICommand
{
public:
    using Action = std::function<void(IShape*)>;

    ModifyShapesCommand(const std::vector<IShape*>& shapes, Action action);
    void Execute() override;

private:
    std::vector<IShape*> m_shapes;
    Action m_action;
};
