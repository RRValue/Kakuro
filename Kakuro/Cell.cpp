#include "Cell.h"

#include "Line.h"

#include <algorithm>
#include <iterator>

bool Cell::solved() const noexcept
{
    return m_Values.size() == 1;
}

Value Cell::solution() const noexcept
{
    return *m_Values.begin();
}

Cell::CellSet Cell::reduce() noexcept
{
    if(!solved())
        return {};

    auto solved_cells = CellSet{};
    const auto cell_solution = solution();

    for(const auto line : m_Lines)
    {
        auto solved_line_cells = line->reduce(cell_solution, m_Position);
        solved_cells.insert(std::cbegin(solved_line_cells), std::cend(solved_line_cells));
    }

    return solved_cells;
}

void Cell::reduce(const ValueSet& other) noexcept
{
    ValueSet result;
    std::set_intersection(std::cbegin(m_Values), std::cend(m_Values),  //
                          std::cbegin(other), std::cend(other),        //
                          std::inserter(result, std::end(result)));

    m_Values = result;
}

void Cell::reduce(const Value& other) noexcept
{
    m_Values.erase(other);
}