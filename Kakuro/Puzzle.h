#pragma once

#include "CoordianateSystem.h"
#include "InputLine.h"

#include <vector>

struct Puzzle
{
    using InputLines = std::vector<InputLine>;

    void addLine(const InputLine& line) noexcept;

    void init() noexcept;

    void reset() noexcept;

    Size m_Size = {};
    InputLines m_InputLines = {};
};