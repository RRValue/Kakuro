#include "Size.h"

void Size::extend(const Size& other) noexcept
{
    width = std::max(width, other.width);
    height = std::max(height, other.height);
};