#include "Puzzle.h"

#include "Cell.h"
#include "Line.h"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <deque>

void Puzzle::addLine(const InputLine& line) noexcept
{
    m_InputLines.push_back(line);
}

void Puzzle::init() noexcept
{
    calculateSize();
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

void Puzzle::calculateSize() noexcept
{
    m_Size = {};

    for(const auto& line : m_InputLines)
        m_Size.extend(line.extend());
}

void Puzzle::create() noexcept
{
    // create board
    m_Board = Board(m_Size.width * m_Size.height);

    for (Index i = 0; i < m_Size.width * m_Size.height; i++)
    {
        m_Board[i] = std::make_shared<Cell>();
        m_Board[i]->m_Position = Point{i % m_Size.width, i / m_Size.height};
    }

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

        auto line_pos = line->m_Origin;

        for(Index i = 0; i < line->m_Length; i++)
        {
            auto* const cell = m_Board[line_pos.x + line_pos.y * m_Size.width].get();

            line->m_Cells[i] = cell;
            cell->m_Lines.insert(line.get());
            line_pos += line->m_Direction;
        }
    }

    auto values = ValueVector(sm_NumDigits);
    std::iota(std::begin(values), std::end(values), sm_MinDigit);
    const auto value_set = ValueSet(std::cbegin(values), std::cend(values));

    for(const auto& cell : m_Board)
        cell->m_Values = value_set;
}

void Puzzle::solve() noexcept
{
    // reduce on sum
    for(const auto& line : m_Lines)
    {
        const auto valid_values = line->getValidValues();

        for(const auto& line_cell : line->m_Cells)
            line_cell->reduce(valid_values);
    }

    // find solved cells
    auto candidates = std::deque<Cell*>();

    for(const auto& cell : m_Board)
    {
        if(!cell->solved())
            continue;

        candidates.push_back(cell.get());
    }

    // reduce on solved cells & process newly solved cells
    while(!candidates.empty())
    {
        const auto cell = candidates.back();
        candidates.pop_back();

        const auto new_candidates = cell->reduce();
        candidates.insert(std::end(candidates), std::cbegin(new_candidates), std::cend(new_candidates));
    }
}