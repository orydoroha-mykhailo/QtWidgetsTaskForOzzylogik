#pragma once

#include <QAbstractItemModel>

#include "data_item.h"
#include "database_manager.h"

class DataModel: public QAbstractItemModel
{
Q_OBJECT
public:
    enum CustomRole
    {
        Mcc = Qt::UserRole,
        Mnc,
        Name
    };

    DataModel(QObject* parent = nullptr);
    ~DataModel() override;

    int           columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant      data(const QModelIndex& index,
                       int role = Qt::DisplayRole) const override;
    bool          setData(const QModelIndex &index, const QVariant &value,
                          int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant      headerData(int section, Qt::Orientation orientation,
                             int role = Qt::DisplayRole) const override;
    QModelIndex   index(int row, int column,
                        const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex   parent(const QModelIndex& index) const override;
    int           rowCount(const QModelIndex& parent = QModelIndex()) const override;
    void          setRoot(DataItem* item);
    DataItem*     itemFromIndex(const QModelIndex& index) const;
    void          updateModel();

private:
    void setupModel(DataItem* parent);
    DataItem* rootItem;
    DatabaseManager &m_DatabaseManager;
};
