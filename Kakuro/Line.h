#pragma once

#include "InputLine.h"
#include "Orientation.h"

struct Cell;

constexpr Point getDirection(const auto& orientation) noexcept
{
    switch(orientation)
    {
        case Orientation::Horinzontal: return Point{1, 0};
        case Orientation::Vertical: return Point{0, 1};
        default: return Point(0, 0);
    }
}

struct Line : InputLine
{
    using Cells = std::vector<Cell*>;

    ValuetSet getValidValues() const noexcept;

    Cells m_Cells;
};