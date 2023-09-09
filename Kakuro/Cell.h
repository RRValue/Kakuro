#pragma once

#include "Definitions.h"

struct Line;

struct Cell
{
    using Lines = std::set<Line*>;

    void reduce(const ValuetSet& other) noexcept;
    void reduce(const Value& other) noexcept;
    bool solved() const noexcept;
    Value solution() const noexcept;

    ValuetSet m_Values = {};
    Lines m_Lines = {};
};