#ifndef PROGRESSLISTWIDGETITEM_H
#define PROGRESSLISTWIDGETITEM_H

#include <QStyledItemDelegate>
#include <QListWidgetItem>
#include <QFontMetrics>

class ProgressListWidgetItem : public QStyledItemDelegate
{
  public:
    explicit ProgressListWidgetItem(QListWidget* parent = 0);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const{
      int height = option.fontMetrics.height();

      return QSize(200, height+8);
    }

};

#endif // PROGRESSLISTWIDGETITEM_H
