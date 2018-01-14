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
  int level = index.data(Outline::HEADING_LEVEL_ROLE).toInt();  
  painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, title, &r);

  QModelIndex nextIdx = index.sibling(index.row()+1, index.column());
  
  // find next block on same level
  while(nextIdx.isValid() && nextIdx.data(Outline::HEADING_LEVEL_ROLE).toInt() != level) {
    nextIdx = nextIdx.sibling(nextIdx.row()+1, index.column());
  }

  QTextBlock next = nextIdx.data(Outline::TEXT_BLOCK_ROLE).value<QTextBlock>();
  QTextBlock block = index.data(Outline::TEXT_BLOCK_ROLE).value<QTextBlock>();

  double position = (double)block.position() / block.document()->characterCount();
  double nextPos  = position;

  if(next.isValid())
      nextPos = (double)next.position() / next.document()->characterCount();

  int width = static_cast<const QListWidget*>(option.widget)->viewport()->width() - 2;

  int right = width * nextPos;
  int left = width * position;
  painter->setPen(Qt::white);

  QPen line(option.palette.color(QPalette::Foreground).darker(50*level));
  painter->setPen(line);
  painter->drawLine(left, r.bottom()+1, left, r.bottom() - 1);
  painter->drawLine(right, r.bottom()+1, right, r.bottom() - 1);
  painter->drawLine(right, r.bottom(), left, r.bottom());
  painter->restore();
}
