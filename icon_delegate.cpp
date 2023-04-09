#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QMouseEvent>

#include "icon_delegate.h"
#include "data_model.h"

IconDelegate::IconDelegate(QObject* parent /* = nullptr */)
{
    m_closeIcon = qApp->style()->standardPixmap(QStyle::SP_DialogCloseButton);

}

void IconDelegate::paint(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    if(index.parent().isValid() && option.state & QStyle::State_MouseOver)
    {
        painter->drawPixmap(closeIconPosition(option, index), m_closeIcon);
    }
    QStyledItemDelegate::paint(painter,option,index);
}

bool IconDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index)
{
    if(index.parent().isValid())
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            closeButtonEvent(event, option, index);
        }

        if(event->type() == QEvent::MouseButtonDblClick)
        {
            emit itemDoubleClick(index);
        }
    }

    return false;
    Q_UNUSED(model)
}

QPoint IconDelegate::closeIconPosition(const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    auto item = static_cast<DataItem*>(index.parent().internalPointer());
    QPixmap icon(item->getImagePath());
    auto text = index.data(Qt::DisplayRole).toString();

    auto indentationSize = qApp->style()->pixelMetric(
                                    QStyle::PM_TreeViewIndentation);

    return QPoint(icon.width() * 2 + QFontMetrics({}).horizontalAdvance(text) +
                  indentationSize + m_margins,
                  option.rect.center().y() - icon.height() / 2);
}

void IconDelegate::closeButtonEvent(QEvent *event,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index)
{
    auto mouseEvent = static_cast<QMouseEvent*>(event);
    auto closeButtonRect = m_closeIcon.rect()
            .translated(closeIconPosition(option, index));

    if(closeButtonRect.contains(mouseEvent->pos()))
    {
        emit closeButtonClick(index.data(DataModel::Mcc).toInt(),
                              index.data(DataModel::Mnc).toInt());
    }
}
