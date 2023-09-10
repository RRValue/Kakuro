#include "Line.h"

#include "Cell.h"

#include <algorithm>
#include <numeric>
#include <iterator>

ValueSet Line::getValidValues() const noexcept
{
    return getValidValues(m_Length, m_Sum);
}

ValueSet Line::getValidValues(const Length& length, const Value& sum) const noexcept
{
    if(length == 0 || length > sm_NumDigits)
        return {};

    auto values = ValueVector(sm_NumDigits);
    std::iota(std::begin(values), std::end(values), sm_MinDigit);

    auto perm = ValueVector(sm_NumDigits, Value(0));
    std::fill_n(std::begin(perm), length, Value(1));

    auto result = ValueSet();

    do
    {
        auto perm_value = ValueVector(sm_NumDigits, Value(0));
        for(Index i = 0; i < sm_NumDigits; i++)
            perm_value[i] = values[i] * perm[i];

        std::erase(perm_value, 0);

        if(std::accumulate(std::cbegin(perm_value), std::cend(perm_value), Value(0)) == sum)
            result.insert(std::cbegin(perm_value), std::cend(perm_value));

    } while(std::prev_permutation(std::begin(perm), std::end(perm)));

    return result;
}

Line::CellSet Line::reduce(const Value& value, const Point& position)
{
    const auto solved_cells_by_cell = reduceCells(value, position);
    const auto solved_cells_by_value = reduceValues();
    auto solved_cells = CellSet{};

    std::set_union(std::cbegin(solved_cells_by_cell), std::cend(solved_cells_by_cell),    //
                   std::cbegin(solved_cells_by_value), std::cend(solved_cells_by_value),  //
                   std::inserter(solved_cells, std::end(solved_cells)));

    return solved_cells;
}

Line::CellSet Line::reduceCells(const Value& value, const Point& position) const noexcept
{
    auto solved_cells = CellSet();

    for(const auto cell : m_Cells)
    {
        if(cell->m_Position == position || cell->solved())
            continue;

        cell->reduce(value);

        if(!cell->solved())
            continue;
            
        solved_cells.insert(cell);
    }

    return solved_cells;
}

Line::CellSet Line::reduceValues() const noexcept
{
    auto length = m_Length;
    auto sum = m_Sum;

    for(const auto cell : m_Cells)
    {
        if(!cell->solved())
            continue;

        length--;
        sum -= cell->solution();
    }

    if(length == m_Length)
        return {};

    auto solved_cells = CellSet();
    const auto values = getValidValues(length, sum);

    for(const auto cell : m_Cells)
    {
        if(cell->solved())
            continue;

        cell->reduce(values);

        if(!cell->solved())
            continue;

        solved_cells.insert(cell);
    }

    return solved_cells;
}