#pragma once

#include "Orientation.h"
#include "Point.h"
#include "Size.h"

struct InputLine
{
    InputLine(const Value& sum, const Point& origin, const Length& length, const Orientation& orientation) noexcept;

    Size extend() const noexcept;
    constexpr Point getDirection(const auto& orientation) noexcept;

    Value m_Sum = 0;
    Point m_Origin = {};
    Length m_Length = 0;
    Orientation m_Orientation = Orientation::Horinzontal;
    Point m_Direction = {};
};