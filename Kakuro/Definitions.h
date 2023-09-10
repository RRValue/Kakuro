#pragma once

#include <set>
#include <vector>

using CoordianteValue = size_t;
using Index = size_t;
using Length = size_t;

using Value = unsigned int;
using ValueSet = std::set<Value>;
using ValueVector = std::vector<Value>;

static const Value sm_MinDigit = Value(1);
static const Value sm_MaxDigit = Value(9);
static const Index sm_NumDigits = Index(sm_MaxDigit) - Index(sm_MinDigit) + Index(1);