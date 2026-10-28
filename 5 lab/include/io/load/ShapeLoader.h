#pragma once
#include "io/load/ShapeData.h"
#include "io/load/ShapeBuildDirector.h"
#include "core/IShape.h"
#include <vector>
#include <memory>
#include <string>

// Template Method: скелет загрузки фигур из файла.
// Конкретные форматы (текст/бинарь) переопределяют шаги.
class ShapeLoader
{
public:
    virtual ~ShapeLoader() = default;

    // Template Method — НЕ виртуальный
    std::vector<std::unique_ptr<IShape>> Load(const std::string& path);

protected:
    virtual void OpenFile(const std::string& path) = 0;
    virtual bool HasMoreShapes() = 0;
    virtual ShapeData ReadNextShapeData() = 0;
    virtual void CloseFile() = 0;

private:
    ShapeBuildDirector m_director;
};