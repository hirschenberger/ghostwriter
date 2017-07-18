/***********************************************************************
 *
 * Copyright (C) 2017 hirschenberger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#ifndef OUTLINEITEMDELEGATE_H
#define OUTLINEITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QListWidgetItem>
#include <QFontMetrics>

class OutlineItemDelegate : public QStyledItemDelegate
{
  public:
    explicit OutlineItemDelegate(QListWidget* parent = 0);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    QSize sizeHint ( const QStyleOptionViewItem& option, const QModelIndex&) const{
      int height = option.fontMetrics.height();

      return QSize(200, height+8);
    }

};

#endif // OUTLINEITEMDELEGATE_H
