#include "Point.h"

void Point::operator+=(const Point& other) noexcept
{
    x += other.x;
    y += other.y;
}