#include "data_item.h"

DataItem::DataItem(const InitItem &data)
    : m_imagePath(data.imagePath),
      m_fullName(data.fullName),
      m_name(data.name),
      m_mcc(data.mcc),
      m_mnc(data.mnc),
      m_parent(nullptr)
{

}

DataItem::~DataItem()
{
    qDeleteAll(child);
}

int DataItem::row() const
{
    return m_parent
        ? m_parent->child.indexOf(const_cast<DataItem*>(this))
        : 0;
}

DataItem *DataItem::childAt(int row) const
{
    return child.value(row);
}

int DataItem::childCount() const
{
    return child.count();
}

DataItem *DataItem::parent() const
{
    return m_parent;
}

QString DataItem::getImagePath() const
{
    return m_imagePath;
}

void DataItem::setImagePath(const QString &imagePath)
{
    m_imagePath = imagePath;
}

QString DataItem::getName() const
{
    return m_name;
}

void DataItem::setName(const QString &name)
{
    m_name = name;
}

QString DataItem::getMcc() const
{
    return m_mcc;
}

void DataItem::setMcc(const QString &mcc)
{
    m_mcc = mcc;
}

QString DataItem::getMnc() const
{
    return m_mnc;
}

void DataItem::setMnc(const QString &mnc)
{
    m_mnc = mnc;
}

QString DataItem::getFullName() const
{
    return m_fullName;
}

void DataItem::setFullName(const QString &fullName)
{
    m_fullName = fullName;
}
