#pragma once

#include "InputLine.h"
#include "Orientation.h"

struct Cell;

struct Line : InputLine
{
    using Cells = std::vector<Cell*>;

    ValuetSet getValidValues() const noexcept;
    void reduce(const Value& value, const Point& position) const noexcept;

    Cells m_Cells;
};