#include "CellSumTest.h"

#include <algorithm>
#include <iterator>
#include <numeric>

CellSumTest::CellSumTest(const ValueSets& valueSets, const Index& set, const Value& sum) noexcept :
    m_ValuesSets{valueSets},  //
    m_SetCount{valueSets.size()},
    m_Set{set},
    m_Sum{sum},
    m_NumCombinations{getCombinationSize(valueSets, set)}
{
}

Index CellSumTest::getCombinationSize(const ValueSets& valueSets, const Index& set) const noexcept
{
    auto num_combinations = Index(1);
    const auto num_sets = valueSets.size();

    for(Index i = 1; i < num_sets; i++)
        num_combinations *= valueSets[(set + i) % num_sets]->size();

    return num_combinations;
}

ValueSet CellSumTest::test() const noexcept
{
    auto rejected = ValueSet();

    for(const auto& value : *m_ValuesSets[m_Set])
    {
        auto combinations = ValueVectors();
        combinations.reserve(m_NumCombinations);

        auto combination = ValueVector(m_SetCount, value);
        auto used_values = ValueSet{value};

        build(1, m_Set + 1, used_values, combination, combinations);

        // ask question
        if(!std::any_of(std::cbegin(combinations), std::cend(combinations),
                        [&](const auto& combination) {  //
                            return m_Sum == std::accumulate(std::cbegin(combination), std::cend(combination), Value(0));
                        }))
        {
            rejected.insert(value);
        }
    }

    const auto& old_values = *m_ValuesSets[m_Set];
    auto new_values = ValueSet();

    std::set_difference(std::cbegin(old_values), std::cend(old_values),  //
                        std::cbegin(rejected), std::cend(rejected),      //
                        std::inserter(new_values, std::end(new_values)));

    return new_values;
}

void CellSumTest::build(const Index& i, const Index& set, ValueSet& usedValues, ValueVector& combination, ValueVectors& combinations) const noexcept
{
    if(i == m_SetCount)
    {
        combinations.push_back(combination);

        return;
    }

    const auto& current_value_set = *m_ValuesSets[set % m_SetCount];
    auto value_set = ValueSet();

    std::set_difference(std::cbegin(current_value_set), std::cend(current_value_set),  //
                        std::cbegin(usedValues), std::cend(usedValues),                //
                        std::inserter(value_set, std::end(value_set)));

    if(value_set.empty())
        return;

    for(const auto& value : value_set)
    {
        combination[i] = value;
        usedValues.insert(value);

        build(i + 1, set + 1, usedValues, combination, combinations);

        usedValues.erase(value);
    }
}