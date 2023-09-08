#pragma once

#include "Point.h"
#include "Orientation.h"

struct InputLine
{
    Value m_Sum = 0;
    Point m_Origin = {};
    Length m_Length = 0;
    Orientation m_Orientation = Orientation::Horinzontal;
};