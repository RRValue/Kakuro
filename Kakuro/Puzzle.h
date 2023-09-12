#pragma once

#include "Size.h"
#include "InputLine.h"

#include <vector>
#include <memory>

struct Line;
struct Label;
struct Cell;

class Puzzle
{
    using InputLines = std::vector<InputLine>;
    
    using LinePtr = std::shared_ptr<Line>;
    using LabelPtr = std::shared_ptr<Label>;
    using CellPtr = std::shared_ptr<Cell>;
    
    using Lines = std::vector<LinePtr>;
    using Labels = std::vector<LabelPtr>;
    using Board = std::vector<CellPtr>;

public:
    void addLine(const InputLine& line) noexcept;
    void init() noexcept;
    void solve() noexcept;
    void reset() noexcept;

    const Size& getSize() const noexcept;

    LabelPtr getLabel(const Index& x, const Index& y) const noexcept;
    CellPtr getCell(const Index& x, const Index& y) const noexcept;

private:
    void calculateSize() noexcept;
    void create() noexcept;
    void setup() noexcept;

private:
    Size m_Size = {};
    InputLines m_InputLines = {};
    
    Lines m_Lines;
    Labels m_Labels;
    Board m_Board;
};