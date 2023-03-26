#include "icon_delegate.h"

IconDelegate::IconDelegate(QObject* parent /* = nullptr */)
{

}

void IconDelegate::paint(QPainter *painter,
  const QStyleOptionViewItem &option,
  const QModelIndex &index) const
{

}

bool IconDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
  const QStyleOptionViewItem &option,
  const QModelIndex &index)
{
    return false;
}
