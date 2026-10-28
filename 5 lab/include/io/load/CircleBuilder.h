#pragma once
#include "io/load/IShapeBuilder.h"
#include "core/CPoint.h"

class CircleBuilder : public IShapeBuilder
{
public:
    void Reset() override;
    void SetType(const std::string& type) override;
    void AddPoint(const CPoint& p) override;
    void SetRadius(double radius) override;
    std::unique_ptr<IShape> GetResult() override;

private:
    CPoint m_center;
    double m_radius = 0.0;
    bool m_hasCenter = false;
};