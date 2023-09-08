#include "Point.h"

void Point::operator+=(const Point& other) noexcept
{
    x += other.x;
    y += other.y;
}

bool Point::operator==(const Point& other) const noexcept
{
    if(this == &other)
        return true;

    return x == other.x &&  //
           y == other.y;
}