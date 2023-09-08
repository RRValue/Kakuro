#include "InputLine.h"

Size InputLine::extend() const noexcept
{
    switch(m_Orientation)
    {
        case Orientation::Horinzontal:
            return {m_Origin.x + m_Length,  //
                    m_Origin.y + 1};
        case Orientation::Vertical:
            return {m_Origin.x + 1,  //
                    m_Origin.y + m_Length};
        default: return {};
    }
}