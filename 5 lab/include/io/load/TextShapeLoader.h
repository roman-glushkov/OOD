#pragma once
#include "io/load/ShapeLoader.h"
#include <fstream>
#include <string>

class TextShapeLoader : public ShapeLoader
{
protected:
    void OpenFile(const std::string& path) override;
    bool HasMoreShapes() override;
    ShapeData ReadNextShapeData() override;
    void CloseFile() override;

private:
    std::string ReadLine();     
    std::ifstream m_in;
    std::string m_currentLine;
    bool m_hasLine = false;
};