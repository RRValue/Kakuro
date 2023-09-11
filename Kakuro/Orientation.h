#pragma once

#include <QtCOre/QFlags>

enum class Orientation
{
    None = 0x0,
    Horinzontal = 0x1,
    Vertical = 0x2,
};

Q_DECLARE_FLAGS(Orientations, Orientation)