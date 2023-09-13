#include "PuzzleDelegate.h"

#include "PuzzleItemData.h"

#include <QtGui/QPainter>

PuzzleDelegate::PuzzleDelegate(QObject* parent) : QAbstractItemDelegate(parent), m_CellSize(20)
{
}

void PuzzleDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, Qt::GlobalColor::white);

    const auto item_data = index.model()->data(index, Qt::DisplayRole).value<PuzzleItemData>();

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    switch(item_data.m_Type)
    {
        case(PuzzleItemData::Type::None): { 
            break;
        }
        case(PuzzleItemData::Type::Label): {
            const auto& orientation = item_data.m_Orientation;
            
            if(orientation.testFlag(Orientation::Horinzontal))
                ;
            else if(orientation.testFlag(Orientation::Vertical))
                ;
            else
                ;
            break;
        }
        case(PuzzleItemData::Type::Cell): { break;
        }
    }

    painter->restore();
}

QSize PuzzleDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(m_CellSize, m_CellSize);
}