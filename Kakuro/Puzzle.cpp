#include "Puzzle.h"

#include "Cell.h"
#include "Label.h"
#include "Line.h"

#include <algorithm>
#include <deque>
#include <iterator>
#include <numeric>

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
    m_Labels = {};
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
    // create board and labels
    m_Board = Board(m_Size.width * m_Size.height);
    m_Labels = Labels(m_Size.width * m_Size.height);

    for(const auto& line : m_InputLines)
    {
        auto position = line.m_Origin;
        const auto direction = line.m_Direction;

        for(Length l = 0; l < line.m_Length + 1; l++)
        {
            const auto index = (position.x + position.y * m_Size.width);

            if(l == 0)  // create labels
            {
                const auto& label_at_vector = m_Labels[index];
                const auto label = label_at_vector ? label_at_vector : std::make_shared<Label>();

                label->m_Type |= line.m_Orientation;

                switch(line.m_Orientation)
                {
                    case Orientation::Horinzontal: {
                        label->m_LabelH = line.m_Sum;
                        break;
                    }
                    case Orientation::Vertical: {
                        label->m_LabelV = line.m_Sum;
                        break;
                    }
                    default: break;
                }

                m_Labels[index] = label;
            }
            else  // create cells
            {
                const auto& cell_at_index = m_Board[index];

                if(!cell_at_index)
                {
                    const auto cell = std::make_shared<Cell>();
                    cell->m_Position = position;

                    m_Board[index] = cell;
                }
            }

            position += direction;
        }
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
        line_pos += line->m_Direction;

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
        if(cell)
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
        if(!cell || !cell->solved())
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

        if(!candidates.empty())
            continue;

        for(const auto& line : m_Lines)
        {
            if(line->solved())
                continue;

            const auto new_candidates = line->reduceByTest();
            candidates.insert(std::end(candidates), std::cbegin(new_candidates), std::cend(new_candidates));
        }
    }
}

const Size& Puzzle::getSize() const noexcept
{
    return m_Size;
}

Puzzle::LabelPtr Puzzle::getLabel(const Index& x, const Index& y) const noexcept
{
    const auto index = x + y * m_Size.width;

    return index < m_Labels.size() ? m_Labels[index] : LabelPtr{};
}

Puzzle::CellPtr Puzzle::getCell(const Index& x, const Index& y) const noexcept
{
    const auto index = x + y * m_Size.width;

    return index < m_Board.size() ? m_Board[index] : CellPtr{};
}