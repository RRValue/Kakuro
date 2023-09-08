#include "Puzzle.h"

#include "Cell.h"
#include "Line.h"

#include <algorithm>
#include <iterator>

void Puzzle::addLine(const InputLine& line) noexcept
{
    m_InputLines.push_back(line);
}

void Puzzle::init() noexcept
{
    m_Size = calculateSize();
    create();
    setup();
}

void Puzzle::reset() noexcept
{
    m_Size = {};
    m_InputLines = {};
    m_Lines = {};
    m_Board = {};
}

Size Puzzle::calculateSize() const noexcept
{
    Size size = {};

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

        size.width = std::max(size.width, extend.width);
        size.height = std::max(size.height, extend.height);
    }

    return size;
}

void Puzzle::create() noexcept
{
    // create board
    m_Board = Board(m_Size.width * m_Size.height);

    for(auto& cell : m_Board)
        cell = std::make_shared<Cell>();

    // create lines
    m_Lines = {};
    m_Lines.reserve(m_InputLines.size());

    std::transform(std::cbegin(m_InputLines), std::cend(m_InputLines),  //
                   std::back_inserter(m_Lines),                         //
                   [](const auto& inputLine) { return std::make_shared<Line>(inputLine); });
}

void Puzzle::setup() noexcept
{
    for(const auto& line : m_Lines)
    {
        line->m_Cells = {};
        line->m_Cells.resize(line->m_Length);

        auto origin = line->m_Origin;
        auto step = [](const auto& orientation) {
            switch(orientation)
            {
                case Orientation::Horinzontal: return Point{1, 0};
                case Orientation::Vertical: return Point{0, 1};
                default: return Point(0, 0);
            }
        }(line->m_Orientation);

        for(Index i = 0; i < line->m_Length; i++)
        {
            auto* const cell = m_Board[origin.x + origin.y * m_Size.width].get();

            line->m_Cells[i] = cell;
            cell->m_Lines.insert(line.get());
            origin += step;
        }
    }
}