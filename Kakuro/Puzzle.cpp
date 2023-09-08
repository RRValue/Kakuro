#include "Puzzle.h"

void Puzzle::addLine(const InputLine& line) noexcept
{
    m_InputLines.push_back(line);
}

void Puzzle::init() noexcept
{
    for(const auto& line : m_InputLines)
    {
        // every line must have length > 0
        if(line.m_Length == 0)
            continue;

        const auto extend = [&line]() -> Size {
            switch(line.m_Orientation)
            {
                case Orientation::Horinzontal:
                    return {line.m_Origin.x + line.m_Length,  //
                            line.m_Origin.y + 1};
                case Orientation::Vertical:
                    return {line.m_Origin.x + 1,  //
                            line.m_Origin.y + line.m_Length};
                default: return {};
            }
        }();

        m_Size.width = std::max(m_Size.width, extend.width);
        m_Size.height = std::max(m_Size.height, extend.height);
    }
}

void Puzzle::reset() noexcept
{
    m_Size = {};
    m_InputLines = {};
}