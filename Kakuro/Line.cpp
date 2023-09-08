#include "Line.h"

#include <algorithm>
#include <numeric>

ValuetSet Line::getValidValues() const noexcept
{
    if(m_Length == 0 || m_Length > sm_NumDigits)
        return {};

    auto values = ValueVector(sm_NumDigits);
    std::iota(std::begin(values), std::end(values), sm_MinDigit);

    auto perm = ValueVector(sm_NumDigits, Value(0));
    std::fill_n(std::begin(perm), m_Length, Value(1));

    auto result = ValuetSet();

    do
    {
        auto perm_value = ValueVector(sm_NumDigits, Value(0));
        for(Index i = 0; i < sm_NumDigits; i++)
            perm_value[i] = values[i] * perm[i];

        std::erase(perm_value, 0);

        if(std::accumulate(std::cbegin(perm_value), std::cend(perm_value), Value(0)) == m_Sum)
            result.insert(std::cbegin(perm_value), std::cend(perm_value));

    } while(std::prev_permutation(std::begin(perm), std::end(perm)));

    return result;
}