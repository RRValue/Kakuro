#include "PuzzleDelegate.h"

#include "PuzzleItemData.h"

#include <QtGui/QPainter>

#include <algorithm>

PuzzleDelegate::PuzzleDelegate(QObject* parent) : QAbstractItemDelegate(parent), m_CellSize(60)
{
}

void PuzzleDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    const auto item_data = index.model()->data(index, Qt::DisplayRole).value<PuzzleItemData>();
    const auto cell_rect = option.rect;
    const auto text_rect = cell_rect.marginsRemoved({2, 2, 2, 2});

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    auto font = painter->font();
    font.setPointSize(12);
    painter->setFont(font);

    switch(item_data.m_Type)
    {
        case(PuzzleItemData::Type::None):
        {
            painter->fillRect(option.rect, Qt::GlobalColor::gray);

            break;
        }
        case(PuzzleItemData::Type::Label):
        {
            const auto& orientation = item_data.m_Orientation;

            painter->fillRect(option.rect, Qt::GlobalColor::gray);
            painter->setBrush(Qt::GlobalColor::black);
            painter->drawLine(cell_rect.topLeft(), cell_rect.bottomRight());

            if(orientation.testFlag(Orientation::Horinzontal))
            {
                painter->setBrush(Qt::GlobalColor::black);
                painter->drawText(text_rect, Qt::AlignRight | Qt::AlignTop, QString::number(item_data.m_LabelH));
            }
            else if(orientation.testFlag(Orientation::Vertical))
            {
                painter->setBrush(Qt::GlobalColor::black);
                painter->drawText(text_rect, Qt::AlignLeft | Qt::AlignBottom, QString::number(item_data.m_LabelV));
            }

            break;
        }
        case(PuzzleItemData::Type::Cell):
        {
            painter->fillRect(option.rect, Qt::GlobalColor::white);

            const auto values = item_data.m_Values;
            const auto num_values = values.size();
            auto text = QString("");

            auto num_first_row = std::min(3, num_values);
            for (Index i = 0; i < 3 && i < num_values; i++)
            {
                text.append(QString::number(values[i]));
            }

            if (num_values > 3)
            {
                text.append("\n");
                
                for(Index i = 3; i < 6 && i < num_values; i++)
                    text.append(QString::number(values[i]));
            }

            if(num_values > 6)
            {
                text.append("\n");

                for(Index i = 6; i < num_values; i++)
                    text.append(QString::number(values[i]));
            }

            painter->setBrush(Qt::GlobalColor::black);
            painter->drawText(text_rect, Qt::AlignCenter, text);

            break;
        }
    }

    painter->restore();
}

QSize PuzzleDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(m_CellSize, m_CellSize);
}