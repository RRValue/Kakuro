#pragma once

#include "InputLine.h"
#include "Orientation.h"

struct Cell;

struct Line : InputLine
{
    using Cells = std::vector<Cell*>;

    ValuetSet getValidValues() const noexcept;

    Cells m_Cells;
};