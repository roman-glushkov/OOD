#pragma once
#include "io/load/IShapeBuilder.h"
#include "core/CPoint.h"
#include <vector>

class RectangleBuilder : public IShapeBuilder
{
public:
    void Reset() override;
    void SetType(const std::string& type) override;
    void AddPoint(const CPoint& p) override;
    void SetRadius(double radius) override;
    std::unique_ptr<IShape> GetResult() override;

private:
    std::vector<CPoint> m_points;
};