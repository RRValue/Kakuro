#pragma once

#include "Definitions.h"

struct Size
{
    void extend(const Size& other) noexcept;

    CoordianteValue width = 0;
    CoordianteValue height = 0;
};