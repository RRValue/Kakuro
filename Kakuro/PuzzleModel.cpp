#include "PuzzleModel.h"

#include "Cell.h"
#include "Label.h"
#include "Puzzle.h"
#include "PuzzleItemData.h"

#include <QtCore/QSize>

PuzzleModel::PuzzleModel(QObject* parent) : QAbstractTableModel(parent), m_Puzzle{nullptr}
{
}

void PuzzleModel::setPuzzle(const PuzzlePtr& puzzle)
{
    beginResetModel();
    m_Puzzle = puzzle;
    endResetModel();
}

int PuzzleModel::rowCount(const QModelIndex& parent) const
{
    return m_Puzzle->getSize().height;
}

int PuzzleModel::columnCount(const QModelIndex& parent) const
{
    return m_Puzzle->getSize().width;
}

QVariant PuzzleModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return {};

    const auto label = m_Puzzle->getLabel(index.column(), index.row());
    const auto cell = m_Puzzle->getCell(index.column(), index.row());

    auto result = PuzzleItemData{};

    if(label)
    {
        result.m_Type = PuzzleItemData::Type::Label;
        result.m_LabelH = label->m_LabelH;
        result.m_LabelV = label->m_LabelV;
        result.m_Orientation = label->m_Type;
    }
    else if(cell)
    {
        result.m_Type = PuzzleItemData::Type::Cell;
        result.m_Values = ValueVector(std::cbegin(cell->m_Values), std::cend(cell->m_Values));
    }

    return QVariant::fromValue(result);
}

QVariant PuzzleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::SizeHintRole)
        return QSize(1, 1);
    return {};
}

void PuzzleModel::dataChanged() noexcept
{
    beginResetModel();
    endResetModel();
}