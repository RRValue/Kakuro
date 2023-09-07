#include "Puzzle.h"

void Puzzle::addLine(const Line& line) noexcept
{
    m_Lines.push_back(line);
}

void Puzzle::init() noexcept
{

}

void Puzzle::reset() noexcept
{
    m_Origin = {};
    m_Size = {};
    m_Lines = {};
}