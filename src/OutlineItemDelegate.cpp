#include <QPainter>
#include <QPainterPath>
#include <QRect>
#include <QTextDocument>
#include <QTextBlock>

#include "Outline.h"

#include "OutlineItemDelegate.h"

#include <iostream>

Q_DECLARE_METATYPE(QTextBlock)

OutlineItemDelegate::OutlineItemDelegate(QListWidget* parent) :
  QStyledItemDelegate(parent)
{
}

void OutlineItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  painter->save();
  QRect r = option.rect.adjusted(5, 5, 0, 0);

  if(option.state & QStyle::State_Selected){
    QColor highlight = option.palette.color(QPalette::Foreground);
    highlight.setAlpha(100);
    QPainterPath path;
    path.addRoundedRect(r, 5, 5);
    painter->fillPath(path, highlight);
  }

  QString title = index.data(Qt::DisplayRole).toString();
  painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, title, &r);

  QTextBlock block = index.data(Outline::TEXT_BLOCK_ROLE).value<QTextBlock>();

  double position = (double)block.position() / block.document()->characterCount();
  int width = static_cast<const QListWidget*>(option.widget)->viewport()->width() - 2;

  int left = width * position;
  painter->setPen(Qt::white);

  QPen line(option.palette.color(QPalette::Foreground));
  painter->setPen(line);
  painter->drawLine(left, r.bottom()+1, left, r.bottom() - 2);
  painter->restore();
}
