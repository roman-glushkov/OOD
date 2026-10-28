#pragma once
#include "io/load/ShapeLoader.h"
#include <fstream>
#include <cstdint>

class BinaryShapeLoader : public ShapeLoader
{
protected:
    void OpenFile(const std::string& path) override;
    bool HasMoreShapes() override;
    ShapeData ReadNextShapeData() override;
    void CloseFile() override;

private:
    ShapeData ReadOneShape();   // <-- новый приватный метод

    std::ifstream m_in;
    std::uint32_t m_remaining = 0;
};