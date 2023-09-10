#include "Cell.h"

#include <algorithm>
#include <iterator>

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

bool Cell::solved() const noexcept
{
    return m_Values.size() == 1;
}

Value Cell::solution() const noexcept
{
    return *m_Values.begin();
}