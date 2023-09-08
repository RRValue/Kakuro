#pragma once

#include "Definitions.h"

struct Line;

struct Cell
{
    using Lines = std::set<Line*>;

    void reduce(const ValuetSet& other) noexcept;

    ValuetSet m_Values = {};
    Lines m_Lines = {};
};