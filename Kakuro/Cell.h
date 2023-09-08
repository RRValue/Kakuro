#pragma once

#include "Definitions.h"

struct Line;

struct Cell
{
    using Lines = std::set<Line*>;

    ValuetSet m_Values = {};
    Lines m_Lines = {};
};