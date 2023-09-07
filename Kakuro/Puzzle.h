#pragma once

#include "CoordianateSystem.h"
#include "Line.h"

#include <vector>

struct Puzzle
{
    using Lines = std::vector<Line>;

    void addLine(const Line& line) noexcept;

    void init() noexcept;

    void reset() noexcept;

    Point m_Origin = {};
    Size m_Size = {};
    Lines m_Lines = {};
};