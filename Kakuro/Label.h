#pragma once

#include "Definitions.h"
#include "Orientation.h"

struct Label
{
    Orientations m_Type = Orientation::None;
    Value m_LabelH = 0;
    Value m_LabelV = 0;
};