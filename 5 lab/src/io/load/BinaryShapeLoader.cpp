#include "io/load/BinaryShapeLoader.h"
#include "utils/Config.h"
#include <stdexcept>

namespace
{
    template <typename T>
    void Read(std::ifstream& in, T& value)
    {
        in.read(reinterpret_cast<char*>(&value), sizeof(T));
        if (!in)
        {
            throw std::runtime_error(Config::MSG_LOAD_READ_ERROR);
        }
    }
}

void BinaryShapeLoader::OpenFile(const std::string& path)
{
    m_in.open(path, std::ios::binary);
    if (!m_in)
    {
        throw std::runtime_error(Config::MSG_LOAD_OPEN_FAILED + path);
    }
    Read(m_in, m_remaining);
}

bool BinaryShapeLoader::HasMoreShapes()
{
    return m_remaining > 0;
}

ShapeData BinaryShapeLoader::ReadNextShapeData()
{
    ShapeData data = ReadOneShape();
    --m_remaining;
    return data;
}

ShapeData BinaryShapeLoader::ReadOneShape()
{
    std::uint8_t code;
    Read(m_in, code);

    ShapeData data;

    if (code == Config::BINARY_TYPE_TRIANGLE)
    {
        data.type = Config::TYPE_TRIANGLE;
        for (std::size_t i = 0; i < Config::TRIANGLE_POINTS_REQUIRED; ++i)
        {
            double x, y;
            Read(m_in, x); Read(m_in, y);
            data.points.emplace_back(x, y);
        }
    }
    else if (code == Config::BINARY_TYPE_RECTANGLE)
    {
        data.type = Config::TYPE_RECTANGLE;
        for (std::size_t i = 0; i < Config::RECTANGLE_POINTS_REQUIRED; ++i)
        {
            double x, y;
            Read(m_in, x); Read(m_in, y);
            data.points.emplace_back(x, y);
        }
    }
    else if (code == Config::BINARY_TYPE_CIRCLE)
    {
        data.type = Config::TYPE_CIRCLE;
        double cx, cy, r;
        Read(m_in, cx); Read(m_in, cy); Read(m_in, r);
        data.points.emplace_back(cx, cy);
        data.radius = r;
    }
    else if (code == Config::BINARY_TYPE_COMPOSITE)
    {
        data.type = Config::TYPE_COMPOSITE;
        std::uint32_t childCount = 0;
        Read(m_in, childCount);
        for (std::uint32_t i = 0; i < childCount; ++i)
        {
            data.children.push_back(ReadOneShape());   // рекурсия без счётчика
        }
    }
    else
    {
        throw std::runtime_error(Config::MSG_LOAD_UNKNOWN_TYPE);
    }

    return data;
}

void BinaryShapeLoader::CloseFile()
{
    if (m_in.is_open()) m_in.close();
    m_remaining = 0;
}