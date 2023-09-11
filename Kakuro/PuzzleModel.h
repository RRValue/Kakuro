#pragma once

#include <QtCore/QAbstractTableModel>

class Puzzle;

class PuzzleModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    using PuzzlePtr = std::shared_ptr<Puzzle>;

public:
    PuzzleModel(QObject* parent = nullptr);

    void setPuzzle(const PuzzlePtr& puzzle);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    PuzzlePtr m_Puzzle;
};