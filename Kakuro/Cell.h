#pragma once

#include "Definitions.h"
#include "Point.h"

struct Line;

struct Cell
{
    using Lines = std::set<Line*>;

    void reduce(const ValueSet& other) noexcept;
    void reduce(const Value& other) noexcept;
    bool solved() const noexcept;
    Value solution() const noexcept;

    ValueSet m_Values = {};
    Lines m_Lines = {};
    Point m_Position = {};
};