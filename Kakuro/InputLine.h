#pragma once

#include "CoordianateSystem.h"
#include "Orientation.h"

struct InputLine
{
    ValuetSet getValidValues() const noexcept;

    Value m_Sum = 0;
    Point m_Origin = {};
    Length m_Length = 0;
    Orientation m_Orientation = Orientation::Horinzontal;
};