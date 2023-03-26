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

QModelIndex DataModel::index(int row, int column,
                             const QModelIndex& parent) const
{
    return {};
}

QModelIndex DataModel::parent(const QModelIndex& index) const
{
    return {};
}

int DataModel::rowCount(const QModelIndex& parent /* = QModelIndex() */) const
{
    return 0;
}

int DataModel::columnCount(const QModelIndex& parent /* = QModelIndex() */) const
{
    return 0;
}

QVariant DataModel::data(const QModelIndex& index,
                         int role /* = Qt::DisplayRoleconst */) const
{
    return {};
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value,
                        int role /* = Qt::EditRole */)
{
    return false;
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation,
                               int role /* = Qt::DisplayRole */) const
{
    return {};
}

Qt::ItemFlags DataModel::flags(const QModelIndex& index) const
{
    return {};
}

void DataModel::setupModel(DataItem* parent)
{

}

DataModel::~DataModel()
{
    delete rootItem;
}
