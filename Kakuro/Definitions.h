#pragma once

#include <set>
#include <vector>

using CoordianteValue = size_t;
using Index = size_t;
using Length = size_t;

using Value = unsigned int;
using ValueSet = std::set<Value>;
using ValueVector = std::vector<Value>;

constexpr Value sm_MinDigit = Value(1);
constexpr Value sm_MaxDigit = Value(9);
constexpr Index sm_NumDigits = Index(sm_MaxDigit) - Index(sm_MinDigit) + Index(1);