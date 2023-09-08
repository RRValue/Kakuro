#pragma once

#include "InputLine.h"

struct Cell;

struct Line : InputLine
{
    using Cells = std::vector<Cell*>;

    ValuetSet getValidValues() const noexcept;

    Cells m_Cells;
};