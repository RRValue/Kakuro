#pragma once

#include <QtWidgets/QAbstractItemDelegate>

class PuzzleDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    PuzzleDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
    int m_CellSize;
};