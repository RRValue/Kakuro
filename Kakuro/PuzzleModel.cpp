#include "PuzzleModel.h"

#include "Puzzle.h"

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
    return m_Puzzle->getSize().height + 1;
}

int PuzzleModel::columnCount(const QModelIndex& parent) const
{
    return m_Puzzle->getSize().width + 1;
}

QVariant PuzzleModel::data(const QModelIndex& index, int role) const
{
    // todo
    if(!index.isValid() || role != Qt::DisplayRole)
        return {};

    return {};
}

QVariant PuzzleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::SizeHintRole)
        return QSize(1, 1);
    return {};
}