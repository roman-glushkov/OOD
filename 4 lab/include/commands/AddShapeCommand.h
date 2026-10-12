#pragma once
#include "commands/ICommand.h"
#include "core/IShape.h"
#include <memory>
#include <vector>

// добавление фигуры
class AddShapeCommand : public ICommand 
{
public:
    AddShapeCommand(std::vector<std::unique_ptr<IShape>>& shapes, std::unique_ptr<IShape> newShape);
    void Execute() override;

private:
    std::vector<std::unique_ptr<IShape>>& m_shapes;
    std::unique_ptr<IShape> m_newShape;
};
