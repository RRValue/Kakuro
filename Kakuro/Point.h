#pragma once

#include "Definitions.h"

struct Point
{
    CoordianteValue x = 0;
    CoordianteValue y = 0;

    void operator+=(const Point& other) noexcept;
    Point operator+(const Point& other) const;
    bool operator==(const Point& other) const noexcept;
};