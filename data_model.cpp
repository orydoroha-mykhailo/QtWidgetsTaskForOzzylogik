#include <QSqlQuery>
#include <QSqlRecord>
#include <QIcon>

#include "data_model.h"
#include "database_manager.h"

DataModel::DataModel(QObject* parent /* = nullptr */)
    : QAbstractItemModel(parent),
      rootItem(nullptr),
      m_DatabaseManager(DatabaseManager::instance())
{
    rootItem = new DataItem;
    setupModel(rootItem);
}

DataModel::~DataModel()
{
    delete rootItem;
}

void DataModel::setRoot(DataItem* item)
{
    delete rootItem;
    rootItem = item;
}

QModelIndex DataModel::index(int row, int column,
                                   const QModelIndex& parent) const
{
    auto parentItem = itemFromIndex(parent);
    Q_ASSERT(parentItem);
    if(auto item = parentItem->childAt(row))
        return createIndex( row, column, item );

    return {};
}

DataItem* DataModel::itemFromIndex(const QModelIndex& index) const
{
    if(index.isValid())
        if(auto item = static_cast<DataItem*>(index.internalPointer()))
            return item;

    return rootItem;
}

int DataModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;

    auto parentItem = itemFromIndex(parent);
    return parentItem ? parentItem->childCount() : 0;
}

int DataModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 1;
}

QModelIndex DataModel::parent(const QModelIndex& index) const
{
    if(auto childItem = itemFromIndex(index))
    {
        if(auto parentItem = childItem->parent())
        {
            if(parentItem == rootItem)
                return {};

            return createIndex(parentItem->row(), 0, parentItem);
        }
    }

    return {};
}

QVariant DataModel::data(const QModelIndex& index, int role) const
{
    if(!rootItem || !index.isValid() || index.column() < 0)
        return {};

    if(auto item = itemFromIndex(index))
    {
        if(role == Qt::DisplayRole)
            return item->getFullName();

        if(role == Qt::DecorationRole)
            return QIcon(item->getImagePath());

        if(role == CustomRole::Mcc)
            return item->getMcc();

        if(role == CustomRole::Mnc)
            return item->getMnc();

        if(role == CustomRole::Name)
            return item->getName();
    }

    return {};
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value,
                              int role)
{
    if(!index.isValid())
        return false;

    if(auto item = itemFromIndex(index))
    {
        if(role == Qt::EditRole)
            item->setFullName(value.toString());
        else if(role == CustomRole::Name)
            item->setName(value.toString());
        else return false;
    }

    emit dataChanged(index, index);
    return true;
}

QVariant DataModel::headerData(int section,
                                     Qt::Orientation orientation,
                                     int role) const
{
    if(section == 0 && orientation == Qt::Horizontal && role == Qt::DisplayRole)
    return "Countries";

    return {};
}

Qt::ItemFlags DataModel::flags(const QModelIndex& index) const
{
    return index.isValid()
           ? Qt::ItemIsEnabled | Qt::ItemIsSelectable
           : Qt::ItemIsEnabled;
}

void DataModel::setupModel(DataItem* parent)
{
    if(!parent || !parent->child.isEmpty())
        return;

    QList<DataItem*> parents;
    QList<int> levels;
    parents << parent;
    levels << 0;

    auto queryCountries = m_DatabaseManager.countries().readData();
    int countryIndex = queryCountries.record().indexOf("name");
    int mccIndex = queryCountries.record().indexOf("mcc");
    int iconCountryIndex = queryCountries.record().indexOf("code");

    int level = 0;
    DataItem::InitItem data;
    QSqlQuery queryOperators;

    while(queryCountries.next())
    {
        if(level > levels.last())
        {
            if(parents.last()->child.count() > 0)
            {
                auto mcc = queryCountries.value(mccIndex).toInt();
                queryOperators = m_DatabaseManager.operators().readData(mcc);

                parents << parents.last()->child.value(
                               parents.last()->child
                               .count() - 1);
                levels << level;
            }
        }

        if(queryOperators.isSelect())
        {
            while (queryOperators.next())
            {
                data.mcc = queryOperators.value(0).toString();
                data.mnc = queryOperators.value(1).toString();
                data.fullName = QString("%1 (%2, %3)")
                        .arg(queryOperators.value(2).toString(),
                             data.mcc, data.mnc);
                data.name = queryOperators.value(2).toString();

                data.imagePath = QString(":/Assets/Operators/%1_%2.png")
                        .arg(data.mcc, data.mnc);

                auto item = new DataItem(data);
                item->m_parent = parents.last();
                parents.last()->child.append(item);
            }
            parents.pop_back();
            levels.pop_back();
            queryOperators.clear();
            --level;
        }
        else
        {
            data.fullName = queryCountries.value(countryIndex).toString();
            data.imagePath = QString(":/Assets/Countries/%1.png")
                    .arg(queryCountries.value(iconCountryIndex).toString());
            auto item = new DataItem(data);
            item->m_parent = parents.last();
            parents.last()->child.append(item);
            ++level;
        }
    }
}

void DataModel::updateModel()
{
    auto newRoot = new DataItem;
    setRoot(newRoot);
    setupModel(newRoot);
}
