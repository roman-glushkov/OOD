// ShapeFactory.h
#pragma once
#include <memory>
#include <string>
#include "IShape.h"
#include "CPoint.h"

class ShapeFactory {
public:
    static std::shared_ptr<IShape> Create(const std::string& line);
    
private:
    static CPoint ParsePoint(const std::string& str);
    static std::string GetParamValue(const std::string& line, const std::string& paramName);
};