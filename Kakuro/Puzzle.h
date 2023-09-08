#pragma once

#include "Size.h"
#include "InputLine.h"

#include <vector>
#include <memory>

struct Line;
struct Cell;

class Puzzle
{
    using InputLines = std::vector<InputLine>;
    using Lines = std::vector<std::shared_ptr<Line>>;
    using Board = std::vector<std::shared_ptr<Cell>>;

public:
    void addLine(const InputLine& line) noexcept;
    void init() noexcept;
    void reset() noexcept;

private:
    void calculateSize() noexcept;
    void create() noexcept;
    void setup() noexcept;

private:
    Size m_Size = {};
    InputLines m_InputLines = {};
    
    Lines m_Lines;
    Board m_Board;
};