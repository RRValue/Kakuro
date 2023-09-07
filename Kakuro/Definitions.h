#pragma once

#include <set>
#include <vector>

using CoordianteValue = size_t;
using Index = size_t;
using Length = size_t;

using Value = unsigned int;
using ValuetSet = std::set<Value>;
using ValueVector = std::vector<Value>;

static Value sm_MinDigit = Value(1);
static Value sm_MaxDigit = Value(9);
static Index sm_NumDigits = Index(sm_MaxDigit) - Index(sm_MinDigit) + Index(1);