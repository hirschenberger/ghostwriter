#include <QPainter>
#include <QRect>
#include <QTextDocument>
#include <QTextBlock>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

#include "Tasklist.h"

#include "TasklistItemDelegate.h"

Q_DECLARE_METATYPE(QTextBlock)

TasklistItemDelegate::TasklistItemDelegate(QListWidget* parent) :
    QItemDelegate(parent),
    openTask(":/resources/images/task-open-light.svg"),
    closedTask(":/resources/images/task-closed-light.svg")
{
}

void TasklistItemDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option, const QString& title) const
{
    QRect r = option.rect.adjusted(20, 0, 0, 0);
    painter->drawText(r.left(), r.top(), r.width()-10, r.height(), Qt::AlignLeft | Qt::AlignVCenter, title, &r);
}

void TasklistItemDelegate::drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const
{
    switch(state)
    {
        case Qt::Checked:
            closedTask.paint(painter, rect);
            break;
        case Qt::Unchecked:
            openTask.paint(painter, rect);
            break;
    }
}
