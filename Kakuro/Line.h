#pragma once

#include "InputLine.h"
#include "Orientation.h"

struct Cell;

struct Line : InputLine
{
    using Cells = std::vector<Cell*>;
    using CellSet = std::set<Cell*>;

    ValuetSet getValidValues() const noexcept;
    CellSet reduce(const Value& value, const Point& position) const noexcept;

    Cells m_Cells;
};