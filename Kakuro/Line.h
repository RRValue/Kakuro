#pragma once

#include "InputLine.h"
#include "Orientation.h"

struct Cell;

struct Line : InputLine
{
    using Cells = std::vector<Cell*>;
    using CellSet = std::set<Cell*>;

    ValueSet getValidValues() const noexcept;
    ValueSet getValidValues(const Length& length, const Value& sum) const noexcept;
    CellSet reduceCells(const Value& value, const Point& position) const noexcept;

    Cells m_Cells;
};