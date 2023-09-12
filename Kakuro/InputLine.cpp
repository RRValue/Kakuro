#include "InputLine.h"

InputLine::InputLine(const Value& sum, const Point& origin, const Length& length, const Orientation& orientation) noexcept :
    m_Sum{sum}, m_Origin{origin}, m_Length{length}, m_Orientation{orientation}, m_Direction{getDirection(m_Orientation)}
{
}

Size InputLine::extend() const noexcept
{
    switch(m_Orientation)
    {
        case Orientation::Horinzontal:
            return {m_Origin.x + m_Length + 1,  //
                    m_Origin.y + 1};
        case Orientation::Vertical:
            return {m_Origin.x + 1,  //
                    m_Origin.y + m_Length + 1};
        default: return {};
    }
}

constexpr Point InputLine::getDirection(const auto& orientation) noexcept
{
    switch(orientation)
    {
        case Orientation::Horinzontal: return Point{1, 0};
        case Orientation::Vertical: return Point{0, 1};
        default: return Point(0, 0);
    }
}