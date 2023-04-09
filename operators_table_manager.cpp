#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QModelIndex>
#include <QDebug>

#include "operators_table_manager.h"
#include "data_model.h"

OperatorsTableManager::OperatorsTableManager(QSqlDatabase &database)
  : m_Database(database)
{

}

QSqlQuery OperatorsTableManager::readData(int mcc)
{
    QSqlQuery query(m_Database);
    if(!query.exec(QString("SELECT * FROM operators"
                           " WHERE Mcc='%1';").arg(mcc)))
    {
        qDebug() << Q_FUNC_INFO << "Unable to execute query";
    }

    return query;
}

void OperatorsTableManager::updateData(const QModelIndex &index)
{
    QSqlQuery query(m_Database);
    auto command = QString("UPDATE operators "
                           "SET Name = \'%1\' "
                           "WHERE Mcc = \'%2\' "
                           "AND Mnc = \'%3\';")
                   .arg(index.data(DataModel::Name).toString(),
                   index.data(DataModel::Mcc).toString(),
                   index.data(DataModel::Mnc).toString());

    if(!query.exec(command))
    {
        qDebug() << Q_FUNC_INFO << "Unable to make edit operation";
    }
}

void OperatorsTableManager::insertData(std::initializer_list<QString> data)
{
    QSqlQuery query(m_Database);
    query.prepare("INSERT INTO operators (Mcc, Mnc, Name)"
                  "VALUES(?, ?, ?);");

    for(const auto& info : data)
    {
        query.addBindValue(info);
    }

    if(!query.exec())
    {
        qDebug() << Q_FUNC_INFO << "Unable to make insert operation";
    }
}
