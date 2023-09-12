#pragma once

#include "Definitions.h"

#include <optional>

struct PuzzleItemData
{
    enum struct Type
    {
        None,
        Label,
        Cell
    };

    using Solution = std::optional<Value>;

    Type m_Type = Type::None;
    Solution m_Solution = 0;
    Value m_LabelH = 0;
    Value m_LabelV = 0;
};

Q_DECLARE_METATYPE(PuzzleItemData)