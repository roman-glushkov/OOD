#include "io/load/TextShapeLoader.h"
#include "io/parse/ShapeParser.h"
#include "utils/Config.h"
#include <stdexcept>

void TextShapeLoader::OpenFile(const std::string& path)
{
    m_in.open(path);
    if (!m_in)
    {
        throw std::runtime_error(Config::MSG_TEXT_LOAD_OPEN_FAILED + path);
    }
    m_hasLine = false;
}

std::string TextShapeLoader::ReadLine()
{
    std::string line;
    while (std::getline(m_in, line))
    {
        if (!line.empty()) return line;
    }
    return "";
}

bool TextShapeLoader::HasMoreShapes()
{
    if (m_hasLine) return true;

    m_currentLine = ReadLine();
    if (m_currentLine.empty()) return false;

    m_hasLine = true;
    return true;
}

ShapeData TextShapeLoader::ReadNextShapeData()
{
    if (!m_hasLine)
    {
        throw std::runtime_error(Config::MSG_TEXT_LOAD_NO_LINE);
    }

    // --- COMPOSITE ---
    if (m_currentLine.rfind(Config::PREFIX_COMPOSITE, 0) == 0)
    {
        std::size_t countPos = m_currentLine.find(Config::PARAM_COUNT);
        if (countPos == std::string::npos)
        {
            throw std::runtime_error(Config::MSG_TEXT_LOAD_BAD_COMPOSITE);
        }
        std::size_t assignPos = m_currentLine.find(Config::PARAM_ASSIGN, countPos);
        if (assignPos == std::string::npos)
        {
            throw std::runtime_error(Config::MSG_TEXT_LOAD_BAD_COMPOSITE);
        }

        std::size_t childCount = std::stoul(m_currentLine.substr(assignPos + 1));

        m_hasLine = false;

        ShapeData data;
        data.type = Config::TYPE_COMPOSITE;

        for (std::size_t i = 0; i < childCount; ++i)
        {
            if (!HasMoreShapes())
            {
                throw std::runtime_error(Config::MSG_TEXT_LOAD_BAD_COMPOSITE);
            }
            data.children.push_back(ReadNextShapeData());
        }

        return data;
    }

    // --- Простая фигура: через ShapeParser ---
    auto parsed = ShapeParser::Parse(m_currentLine);
    m_hasLine = false;

    ShapeData data;
    data.type   = parsed.type;
    data.points = parsed.points;
    data.radius = parsed.radius;
    return data;
}

void TextShapeLoader::CloseFile()
{
    if (m_in.is_open()) m_in.close();
    m_hasLine = false;
}