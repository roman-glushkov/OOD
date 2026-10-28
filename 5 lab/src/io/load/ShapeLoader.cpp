#include "io/load/ShapeLoader.h"

std::vector<std::unique_ptr<IShape>> ShapeLoader::Load(const std::string& path)
{
    std::vector<std::unique_ptr<IShape>> result;

    try
    {
        OpenFile(path);

        while (HasMoreShapes())
        {
            ShapeData data = ReadNextShapeData();
            result.push_back(m_director.Build(data));
        }

        CloseFile();
    }
    catch (...)
    {
        CloseFile();
        throw;
    }

    return result;
}