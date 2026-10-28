#include "io/save/TextSaveVisitor.h"
#include "shapes/CTriangle.h"
#include "shapes/CRectangle.h"
#include "shapes/CCircle.h"
#include "shapes/CompositeShape.h"
#include "utils/Config.h"
#include <limits>

TextSaveVisitor::TextSaveVisitor(std::ostream& out)
    : m_out(out)
{
    m_out.precision(std::numeric_limits<double>::max_digits10);
}

void TextSaveVisitor::Visit(const CTriangle& shape)
{
    m_out << Config::PREFIX_TRIANGLE
          << Config::PARAM_P1 << Config::PARAM_ASSIGN
          << shape.GetP1().x << Config::COORD_SEPARATOR << shape.GetP1().y
          << Config::PARAM_SEPARATOR << " "
          << Config::PARAM_P2 << Config::PARAM_ASSIGN
          << shape.GetP2().x << Config::COORD_SEPARATOR << shape.GetP2().y
          << Config::PARAM_SEPARATOR << " "
          << Config::PARAM_P3 << Config::PARAM_ASSIGN
          << shape.GetP3().x << Config::COORD_SEPARATOR << shape.GetP3().y
          << Config::NEWLINE;
}

void TextSaveVisitor::Visit(const CRectangle& shape)
{
    m_out << Config::PREFIX_RECTANGLE
          << Config::PARAM_P1 << Config::PARAM_ASSIGN
          << shape.GetP1().x << Config::COORD_SEPARATOR << shape.GetP1().y
          << Config::PARAM_SEPARATOR << " "
          << Config::PARAM_P2 << Config::PARAM_ASSIGN
          << shape.GetP2().x << Config::COORD_SEPARATOR << shape.GetP2().y
          << Config::NEWLINE;
}

void TextSaveVisitor::Visit(const CCircle& shape)
{
    m_out << Config::PREFIX_CIRCLE
          << Config::PARAM_C << Config::PARAM_ASSIGN
          << shape.GetCenter().x << Config::COORD_SEPARATOR << shape.GetCenter().y
          << Config::PARAM_SEPARATOR << " "
          << Config::PARAM_R << Config::PARAM_ASSIGN << shape.GetRadius()
          << Config::NEWLINE;
}

void TextSaveVisitor::Visit(const CompositeShape& shape)
{
    m_out << Config::PREFIX_COMPOSITE << " "
          << Config::PARAM_COUNT << Config::PARAM_ASSIGN
          << shape.GetChildren().size()
          << Config::NEWLINE;

    for (const auto& child : shape.GetChildren())
    {
        child->Accept(*this);
    }
}