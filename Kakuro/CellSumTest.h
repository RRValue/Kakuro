#pragma once

#include "Definitions.h"

class CellSumTest
{
public:
    using ValueSets = std::vector<ValueSet const*>;
    using ValueVectors = std::vector<ValueVector>;

public:
    CellSumTest(const ValueSets& valueSets, const Index& set, const Value& sum) noexcept;
    CellSumTest(const CellSumTest&) = delete;
    CellSumTest(CellSumTest&&) = delete;

    CellSumTest operator=(const CellSumTest&) = delete;
    CellSumTest operator=(CellSumTest&&) = delete;

    ValueSet test() const noexcept;

private:
    void build(const Index& i, const Index& set, ValueSet& usedValues, ValueVector& combination, ValueVectors& combinations) const noexcept;
    Index getCombinationSize(const ValueSets& valueSets, const Index& set) const noexcept;

private:
    const ValueSets m_ValuesSets;
    const Index m_SetCount;
    const Index m_Set;
    const Value m_Sum;
    const Index m_NumCombinations;
};