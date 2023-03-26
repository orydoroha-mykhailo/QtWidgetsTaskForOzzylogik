#include "data_item.h"

DataItem::DataItem(const InitItem& data /* = {} */)
{

}

QString DataItem::getImagePath() const
{
    return {};
}

DataItem::~DataItem()
{
    qDeleteAll(child);
}
