#include "io/load/TextShapeLoader.h"
#include "io/parse/ShapeParser.h"
#include "utils/Config.h"
#include <stdexcept>

namespace
{
    void ParseColor(const std::string& line, const std::string& param, sf::Color& out)
    {
        std::size_t pos = line.find(param + Config::PARAM_ASSIGN);
        if (pos == std::string::npos) return;
        pos += param.size() + 1;

        std::size_t end = line.find(Config::PARAM_SEPARATOR, pos);
        if (end == std::string::npos) end = line.size();

        std::string v = line.substr(pos, end - pos);

        std::size_t c1 = v.find(Config::COORD_SEPARATOR);
        if (c1 == std::string::npos) return;
        std::size_t c2 = v.find(Config::COORD_SEPARATOR, c1 + 1);
        if (c2 == std::string::npos) return;
        std::size_t c3 = v.find(Config::COORD_SEPARATOR, c2 + 1);
        if (c3 == std::string::npos) return;

        int r = std::stoi(v.substr(0, c1));
        int g = std::stoi(v.substr(c1 + 1, c2 - c1 - 1));
        int b = std::stoi(v.substr(c2 + 1, c3 - c2 - 1));
        int a = std::stoi(v.substr(c3 + 1));

        out = sf::Color(
            static_cast<std::uint8_t>(r),
            static_cast<std::uint8_t>(g),
            static_cast<std::uint8_t>(b),
            static_cast<std::uint8_t>(a));
    }

    void ParseFloat(const std::string& line, const std::string& param, float& out)
    {
        std::size_t pos = line.find(param + Config::PARAM_ASSIGN);
        if (pos == std::string::npos) return;
        pos += param.size() + 1;

        std::size_t end = line.find(Config::PARAM_SEPARATOR, pos);
        if (end == std::string::npos) end = line.size();

        out = std::stof(line.substr(pos, end - pos));
    }
}

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

    // --- Стиль (если есть) ---
    ParseColor(m_currentLine, Config::PARAM_OUTLINE, data.outlineColor);
    ParseColor(m_currentLine, Config::PARAM_FILL,    data.fillColor);
    ParseFloat(m_currentLine, Config::PARAM_THICK,   data.thickness);

    return data;
}

void TextShapeLoader::CloseFile()
{
    if (m_in.is_open()) m_in.close();
    m_hasLine = false;
}