#include "Point.h"

void Point::operator+=(const Point& other) noexcept
{
    x += other.x;
    y += other.y;
}

Point Point::operator+(const Point& other) const
{
    auto result = *this;
    result.x += other.x;
    result.y += other.y;

    return result;
}

bool Point::operator==(const Point& other) const noexcept
{
    if(this == &other)
        return true;

    return x == other.x &&  //
           y == other.y;
}