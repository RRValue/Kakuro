#include "Cell.h"

#include <algorithm>
#include <iterator>

void Cell::reduce(const ValuetSet& other) noexcept
{
    ValuetSet result;
    std::set_intersection(std::cbegin(m_Values), std::cend(m_Values),  //
                          std::cbegin(other), std::cend(other),        //
                          std::inserter(result, std::end(result)));

    m_Values = result;
}

void Cell::reduce(const Value& other) noexcept
{
    m_Values.erase(other);
}